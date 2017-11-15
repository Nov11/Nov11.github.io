---
layout: post
title:  "Why MySQL uses threads to handle requests?"
date:   2017-11-15 17:47:41 +0800
categories: jekyll update
---

I followed this [link](https://www.zhihu.com/question/20303558) and found some thing fun. Let me quote this starting from Understanding.Mysql.Internals page 107.
It talks about advantages and disadvantages of threads and processes first. And then the choice. The text is listed below:

>When implementing a server, a programmer is faced with a dilemma as to whether to use threads or processes to handle requests. Both have advantages and disadvantages.
From its very inception, MySQL has used threads. In this chapter we discuss the rationale, strengths and weaknesses, and implementation of thread-based request handling in the MySQL server.


>Threads Versus Processes  
Perhaps the most important difference between a process and a thread is that a child
thread shares the heap (global program data) with the parent, while a child process does
not. This has a number of implications when you are deciding which model to use.


>Advantages of Using Threads  
Threads have been implemented in programming libraries and operating systems
industry-wide for the following reasons:  
• Reduced memory utilization. The memory overhead of creating another thread
is limited to the stack plus some bookkeeping memory needed by the thread
manager.  
• No advanced techniques required to access server-global data. If the data could
possibly be modified by another concurrently running thread, all that needs to
be done is to protect the relevant section with a mutual exclusion lock or mutex
(described later in this chapter). In the absence of such a possibility, the global
data is accessed as if there were no threads to worry about.  
• Creating a thread takes much less time than creating a process because there is
no need to copy the heap segment, which could be very large.  
• The kernel spends less time in the scheduler on context switches between
threads than between processes. This leaves more CPU time for the heavily
loaded server to do its job.

>Disadvantages of Using Threads  
Despite the importance of threads in modern computing, they are known to have
drawbacks:  
• Programming mistakes are very expensive. If one thread crashes, it brings the
whole server down. One rogue thread can corrupt the global data, causing other
threads to malfunction.  
• Programming mistakes are easy to make. A programmer must think constantly
about the possibility of some other thread doing things to cause trouble, and
how to avoid it. An extra-defensive programming approach is required.  
• Threaded servers are notorious for synchronization bugs that are nearly impossible
to duplicate in testing but happen at a very wrong time in production. The
high probability of such bugs is a result of having a shared address space, which
brings on a much higher degree of thread interaction.  
• Mutex contention at some point can get out of hand. If too many threads try to
acquire the same mutex at the same time, this may result in excessive context
switching, with lots of CPU time spent in the kernel scheduler and very little left
to do the job.  
• 32-bit systems are limited to 4 GB address space per process. Since all threads
share the same address space, the whole server is theoretically limited to 4 GB of
RAM even when there is a lot more physical RAM available. In practice the
address space starts getting very crowded at a much smaller limit, somewhere
around 1.5 GB on x86 Linux.  
• The crowded 32-bit address space presents another problem. Each thread needs
some room for its stack. When a stack is allocated, even if the thread does not
use the majority of the allocated space, the address space of the server has to be
reserved for it. Each new stack reduces potential room for the heap. Thus, even
though there might be plenty of physical memory, it may not possible to have
large buffers, to have a lot of concurrent threads, and to give each thread plenty
of room for its stack at the same time.  

>Advantages of Using Forked Processes  
The drawbacks of threads correspond to the strengths of using multiple processes
instead:  
• Programming mistakes are not so fatal. Although a definite possibility, it is not
as easy for a rogue forked-server process to disrupt the whole server.  
• Programming mistakes are much less likely. Most of the time, the programmer
only needs to think of one thread of execution, undisturbed by possible concurrent
intruders.  
• Much fewer phantom bugs. If a bug happens once, it is usually fairly easy to
duplicate it. With its own address space for each forked process, there is not
much interaction between them.  
• On a 32-bit system, the issue of running out of address space is usually not as acute.

>Disadvantages of Using Forked Processes    
To wrap up our overview, I’ll list the problems with multiple processes, which mirror
the advantages of threads:  
• Memory utilization is suboptimal. Possibly large memory segments are copied
unnecessarily when a child is forked.  
• Special techniques are required to share data between processes. This makes it
cumbersome to access the data global to the server.  
• Creating a process requires more overhead in the kernel than creating a thread. One
big performance hit is the need to copy the data segment of the parent process.
Linux, however, cheats in this area by implementing what is called copy-on-write.
The actual copy of a parent process page does not take place until the child or the
parent modifies that page. Until then, both use the same page.  
• Context switches between processes are more time-consuming than between
threads because the kernel needs to switch the pages, file descriptor tables, and
other extra context info. Less time is left for the server to do the actual work.
  
>In summary, a threaded server is ideal when a lot of data needs to be shared between
the connection handlers, and when the programming skills are not lacking. When it
came down to deciding which model was the right one for MySQL, the choice was
clear. A database server needs to have lots of shared buffers, and other shared data.  
As far as the programming skills were concerned, they were not lacking at all. Just as a
good rider becomes one with the horse, Monty had become one with the computer. It
pained him to see system resources wasted. He felt confident enough to be able to write
virtually bug-free code, deal with the concurrency issues presented by threads, and even
work with a small stack. What an exciting challenge! Needless to say, he chose threads.

Well, that's it.
I think DBMS may actually be a interesting area. :) 