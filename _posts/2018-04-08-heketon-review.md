---
layout: post
title:  "Hekaton Paper"
date:   2018-04-09 22:52:59 +0800
categories: jekyll update
---

### 'Compilation in the Microsoft SQL Server Hekaton Engine'
#### What is Hekaton?
An execution engine for MS SQL Server designed for in-memory database OLTP workload.
#### What does it do?
Achieve 100X compared to original disk based SQL Database.
#### How does it get there?
* index for main memory（this reduces instructions on index locking)
* eliminate latches and locks(this makes it scales well on many core machines) using OCC & MVCC & latch-free data structure.
* compile request to native code(this reduces instruction per query)
#### Naive compilation in Hekaton
* reuse SQL Server's T-SQL compilation stack including metadata, parser, name resolution, type derivation and query optimazer.
* Hekaton output is C code.
* use VC++ compiler to convert C code to machine code.
* Output of T-SQL's compilation stack is called mixed abstract tree or MAT. 
* MAT carries meatadata, imperative logic, expressions and query plans.
* MAT is converted to a much simple pure imperative tree or PIT which can be convert to C code easily. (possible for IR of Phoenix or LLVM)
* Machine code sits in form of DLL which will be loaded into Hekaton.
#### Need schema compilation
* Hekaton storage engine treats records as opaque object and need compiler to pass it utility function callbacks to perform operations on data.
* provide mechanism for interpret engine to access Hekaton table.
#### What is the result?
* 10X less instructions from compiled to interpreted on table without index 
* 15X less instructions on table with an index

[jekyll-docs]: http://jekyllrb.com/docs/home
[jekyll-gh]:   https://github.com/jekyll/jekyll
[jekyll-talk]: https://talk.jekyllrb.com/
