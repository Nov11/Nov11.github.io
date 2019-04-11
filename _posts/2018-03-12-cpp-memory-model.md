---
layout: post
title:  "Notes on : C++ memory model @Meeting C++ 2014"
date:   2018-03-12 22:13:00 +0800
categories: jekyll update
---
```
c++ memory model
2018年3月11日
23:53
 
The C++ Memory Model - Valentin Ziegler @ Meeting C++ 2014
 
来自 <https://www.youtube.com/watch?v=gpsz8sc6mNU> 
 
 
Why do we need memory model?
Back to C++03, single thread execution model says that we cannot observe  optimizations performed by the system. Program will behave as-if it was running on its own. And the result is the same as if operations were executed in the order specified by the program.
When it comes to multithreading, optimizations made by system becomes visible.
 
What does memory model tell us?
Describe the interactions of threads through memory and their shared use of data
Tells us if our program has well defined behavior
Constrains code generation for compiler
 
C++ memory model basics:
Data race
Memory location :
An object of scalar type or a maximal sequence of adjacent non-zero width bit-fields
Conflicting action:
two (or more) actions that access the same memory location and at least one of them is a write
Data race:
two conflicting actions in different threads and neither happens before the other
 
Sequential consistency 
the result of any execution is the same as-if
1. the operations of all threads are executed in some sequential order
2. the operations of each thread appear in this sequence in the order specified by their program
C++ memory model:
sequential consistency for data-race-free programs(SC-DRF)
Programmer insures that there is no data race.
System guarantees sequential consistent execution.
 
Synchronization to avoid data race
Locks: unlock synchronizes with lock
atomic<>:  store synchronizes with operations that load the stored value
Atomic<> provides inter-thread synchronization and sequential consistency by default.
 
Meddling with memory order:
Relaxed memory ordering
• Each memory location has a total modification order (however, this order cannot be observed directly)
• Memory operations performed by the same thread on the same memory location are not reordered with respect to the modification order.
Acquire & release memory ordering
• a store-release operation synchronizes with all load-acquire operations reading the stored value.
• All Operations in the releasing thread preceding the store-release happen-before all operations following the load-acquire in the acquiring thread.
Consume & release memory ordering(not fully supported when the talk was given)
• “Light version” of acquire/release
• All Operations in the releasing thread preceding the store-release happen-before an operation X in the consuming thread if X depends on the value loaded.(say X be dereferencing a pointer stored in atomic variable)
Sequential consistency memory ordering
• Global, total order of load and store operations
• At any given time, each memory location has only one value(assuming there are no data races) 
• memory orders make more sense when combined with background that multi-core processor with shared l3 cache but every core has its own l1 & l2 cache.
Dekker's algorithm need this to be correct
atomic<bool> f1=false;
atomic<bool> f2=false;
Thread #1:
f1.store(true, memory_order_seq_cst);
if (!f2.load(memory_order_seq_cst)) {
// critical section
}
Thread #2:
f2.store(true, memory_order_seq_cst);
if (!f1.load(memory_order_seq_cst)) {
// critical section
}
```