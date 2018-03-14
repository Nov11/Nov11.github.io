---
layout: post
title:  "Notes on : CppCon 2015: Michael Wong C++11/14/17 atomics and memory model..."
date:   2018-03-12 22:13:00 +0800
categories: jekyll update
---
```
CppCon 2015: Michael Wong “C++11/14/17 atomics and memory model..."
2018年3月14日
22:10
 
https://www.youtube.com/watch?v=DS2m7T6NKZQ
 
This is not a well-organized  presentation . The one of meeting C++ 2014 is more concise and clear about basic on memory model. Nothing new in this in the first 30min. Not recommended watching.
 
 
content
Motivation why we have a memory model
Teach the memory model
Show use cases
C++ memory model goal
 
Quotes on standards:
• C++11 have multithreading support 
– Memory model, atomics API 
– Language support: TLS, static init, termination, lambda function 
– Library support: thread start, join, terminate, mutex, condition variable 
– Advanced abstractions: basic futures, thread pools 
• C11 will have similar memory model, atomics API. TLS, static init/termination 
– Some minor differences like __Atomic qualifier 
• C++14 enhanced the memory model with better definition of lock- free vs obstruction-free 
– Clarified atomic_signal_fence 
– Improved on out-of-thin-air results
– Realized consume ordering as described was problematic, hence Paul McKenney’s work to improve on it (see his talk)
 • C++17 we are talking about 
– Define strength ordering of memory models
– Execution agents, atomic views, better SC model
 
Sequential consistency :
“… the result of any execution is the same as if the reads and writes occurred in some order, and the operations of each individual processor appear in this sequence in the order specified by its program”
Fence() may be used to limit space of possible interleaving combinations without knowledge of other threads:
Thread 1: Thread2: 
x = 1; w=1; 
r1 = z; r3=y; 
fence(); fence();
y = 1; z=1; 
r2 = w; r4=x; 
Is r3==1 and r4==1 possible? yes
Is r1==1 and r2==1 possible? Yes
Memory model and instruction reordering(not the same)
• Instruction reordering: When a program executes instructions, especially memory reads and writes, in an order that is different than the order specified in the program’s source code. 
• Memory model: Describes how memory reads and writes may appear to be executed relative to their program order.
• Affects the valid optimizations that can be performed by compilers, physical processors, and caches.
Memory model definition
• A set of rules that describe allowable semantics for memory accesses on a computer program 
– Defines the expected value or values returned by any loads in the program
– Determines when a program produces undefined behavior (e.g load from uninitialized variables)
• Stroustrup: represents a contract between the implementers and the programmers to ensure that most programmers do not have to think about the details of modern computer hardware
• critical component of concurrent programming 
• How threads interact through memory
• What assumptions the compiler is allowed to make when
generating code
•it states about how threads interat through memory & what assumptions the compiler is allowed to make when generating code
– How things are laid out in memory
– What happens when two threads access the same memory location
and one of them is a modfy
» Data race(and also memory location definition, two threads one do write and one do (read or write) without happens-before relations results data race and undefined behavior
» Modification order
» Atomicity/isolation
» Visibility
» Ordering
 
Omit the API part.
Memory model constants:
enum memory_order {
memory_order_relaxed,// just atomic, no onstraint
memory_order_release,
memory_order_acquire,
memory_order_consume,
memory_order_acq_rel,// both acquire and release
memory_order_seq_cst};// sequentially consistent
 
• Sequential Consistency
– Single total order for all SC ops on all variables
– default
• Acquire/Release/consume
– Pairwise ordering rather than total order
– Independent Reads of Independent Writes don't require
synchronization between CPUs
• Relaxed Atomics
– Read or write data without ordering
– Still obeys happens-before
• Operations on variable have attributes, which can be explicit
 
Double checked locking from wiki
std::atomic<Singleton*> Singleton::m_instance;
std::mutex Singleton::m_mutex;
Singleton* Singleton::getInstance() {
    Singleton* tmp = m_instance.load(std::memory_order_acquire);
    if (tmp == nullptr) {
        std::lock_guard<std::mutex> lock(m_mutex);
        tmp = m_instance.load(std::memory_order_relaxed);
        if (tmp == nullptr) {
            tmp = new Singleton;
            m_instance.store(tmp, std::memory_order_release);
        }
    }
    return tmp;
}
 
来自 <https://en.wikipedia.org/wiki/Double-checked_locking> 
 
 
```