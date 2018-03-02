---
layout: post
title:  "Why not use mmap in RDBMS?"
date:   2018-03-02 17:19:00 +0800
categories: jekyll update
---
```
Why not using mmap?
2018年2月28日
0:01
 
There are advantages and disadvantages to using memory-mapped I/O. Advantages include:
    1. Many operations, especially I/O intensive operations, can be faster since content does need to be copied between kernel space and user space.
    2. The SQLite library may need less RAM since it shares pages with the operating-system page cache and does not always need its own copy of working pages.
But there are also disadvantages:
    1. An I/O error on a memory-mapped file cannot be caught and dealt with by SQLite. Instead, the I/O error causes a signal which, if not caught by the application, results in a program crash.
    2. The operating system must have a unified buffer cache in order for the memory-mapped I/O extension to work correctly, especially in situations where two processes are accessing the same database file and one process is using memory-mapped I/O while the other is not. Not all operating systems have a unified buffer cache. In some operating systems that claim to have a unified buffer cache, the implementation is buggy and can lead to corrupt databases.
    3. Performance does not always increase with memory-mapped I/O. In fact, it is possible to construct test cases where performance is reduced by the use of memory-mapped I/O.
    4. Windows is unable to truncate a memory-mapped file. Hence, on Windows, if an operation such as VACUUM or auto_vacuum tries to reduce the size of a memory-mapped database file, the size reduction attempt will silently fail, leaving unused space at the end of the database file. No data is lost due to this problem, and the unused space will be reused again the next time the database grows. However if a version of SQLite prior to 3.7.0 runs PRAGMA integrity_check on such a database, it will (incorrectly) report database corruption due to the unused space at the end. Or if a version of SQLite prior to 3.7.0 writes to the database while it still has unused space at the end, it may make that unused space inaccessible and unavailable for reuse until after the next VACUUM.
 
来自 <https://sqlite.org/mmap.html> 
Write in position after the end of file behaves differently among different linux kernel versions.
DBMS wants to make sure certain data is flushed out for sure before it can take further steps. e.g. write ahead logging.
OS running the page-fault routine or background writing-out may stall DB threads. 
```