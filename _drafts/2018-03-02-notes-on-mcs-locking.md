---
layout: post
title:  "Notes on : Mellor-Crummey and Scott locking"
date:   2018-03-02 11:53:00 +0800
categories: jekyll update
---
I found a blog on it. here: https://libfbp.blogspot.co.uk/2018/01/c-mellor-crummey-scott-mcs-lock.html

And an example:

https://gist.githubusercontent.com/ifknot/dffe60f5999f885edc33bdee1b9f2449/raw/d4552c8ddd18713f685f1ea19790c803c5d69402/mcs_lock.cpp

not sure why updated next pointer will eventually be seen by the unlock thread. it seems that the barrier doesn't provide any guarantee on this.

the cpu_relax is asm : pause with memory in clobber list. 

this is the basic idea.
```c++
#include "mcs_lock.h"

namespace sync {

    void mcs_lock::lock() {
        //to acquire the lock a thread atomically appends its own local node at the tail of the list returning tail's previous contents
        auto prior_node = tail.exchange(&local_node,
                                        std::memory_order_acquire);
        if(prior_node != nullptr) {
            local_node.locked = true;
        //if the list was not previously empty, it sets the predecessor’s next field to refer to its own local node
            prior_node->next = &local_node;
        //thread then spins on its local locked field, waiting until its predecessor sets this field to false
            while(local_node.locked)
                cpu_relax();
        }
        //now first in the queue, own the lock and enter the critical section...
    }

    void mcs_lock::unlock() {
        //...leave the critical section
        //check whether this thread's local node’s next field is null
        if(local_node.next == nullptr) {
        //if so, then either:
        // 1. no other thread is contending for the lock
        // 2. there is a race condition with another thread about to
        //to distinguish between these cases atomic compare exchange the tail field
        //if the call succeeds, then no other thread is trying to acquire the lock, tail is set to nullptr, and unlock() returns
            mcs_node* p = &local_node;
            if(tail.compare_exchange_strong(p,nullptr,
                                            std::memory_order_release,
                                            std::memory_order_relaxed)) {
                return;
            }
        //otherwise, another thread is in the process of trying to acquire the lock, so spins waiting for it to finish
        //!!!!!!!!!!!!WHY MODIFICATION IN OTHER THREAD WILL EVENTUALLY BE SEEN BY THIS THREAD?
            while (local_node.next == nullptr) {};
        }
        //in either case, once the successor has appeared, the unlock() method sets its successor’s locked field to false, indicating that the lock is now free
        local_node.next->locked = false;
        //at this point no other thread can access this node and it can be reused
        local_node.next = nullptr;
    }

    thread_local mcs_lock::mcs_node mcs_lock::local_node = mcs_lock::mcs_node{};

}
```

infos related to this implementation:

"memory" in gcc embedded asm  
The "memory" clobber tells the compiler that the assembly code performs memory reads or writes to items other than those listed in the input and output operands (for example, accessing the memory pointed to by one of the input parameters). To ensure memory contains correct values, GCC may need to flush specific register values to memory before executing the asm. Further, the compiler does not assume that any values read from memory before an asm remain unchanged after that asm; it reloads them as needed. Using the "memory" clobber effectively forms a read/write memory barrier for the compiler.

Note that this clobber does not prevent the processor from doing speculative reads past the asm statement. To prevent that, you need processor-specific fence instructions.