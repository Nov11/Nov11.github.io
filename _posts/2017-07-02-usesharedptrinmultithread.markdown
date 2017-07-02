---
layout: post
title:  "C++: use shared_ptr with multithread"
date:   2017-07-02 14:24 +0800
categories: jekyll update
---
[GotW #95 Solution: Thread Safety and Synchronization](https://herbsutter.com/2014/01/13/gotw-95-solution-thread-safety-and-synchronization/)

##### In the role of a user:
shared_ptr it self is not a fully synchronized object. When one shared_ptr is accessed in two threads and two threads just read(or calling const functions) from it, it is correctly synchronized.
***
##### In the role of class implementor:
When implementing a not fully internal synchronized class, one should make sure that :
* if the code knows and owns one shared writable object, the code is responsible to synchronized write and read operations on it. Common techniques are mutex, atomic<>
* concurrent operations on different objects must be safe. no synchronization is needed.
* concurrent const operations on same objects must be safe.
***
##### Partial internal synchronization in shared_ptr:
When it comes to partial internal synchronization, shared_ptr serves as a good example.
 Since the reference counter is a shared variable, it needs to be protected when concurrent write occurs.
  It is not possible for the calling code to know that. So shared_ptr protect the reference count in its implementation.
***
##### Shared_ptr usage example in frequently seen circumstances:
examples about whether the user code is correctly synchronized(these examples are in blog shown in the beginning of this post):
1.
```
// Case A: Using distinct objects

// thread 1 (performs no additional synchronization)
auto x = sp1;                      // read from sp1 (writes the count!)

// thread 2 (performs no additional synchronization)
sp2 = something_else;              // write to sp2 (writes the count!)
```
Here sp1 and sp2 is in no way related. It's correct, because 'concurrent operations on different objects must be safe'.

2.
```
// Case B: const access to the same object

// thread 1 (performs no additional synchronization)
auto sp3 = sp;                     // read from sp (writes the count!)

// thread 2 (performs no additional synchronization)
auto sp4 = sp;                     // read from sp (writes the count!)
```
It's correct, because 'concurrent const operations on same objects must be safe'.

3.
```
// Case C: External synchronization still required as usual
//         for non-const access to same visible shared object

// thread 1
{
    lock_guard hold(mut_sp);           // acquire lock
    auto sp3 = sp;                     // read from sp
}

// thread 2
{
    lock_guard hold(mut_sp);           // acquire lock
    sp = something_else;               // modify sp
}
```
Synchronization is needed. This is the common case that one object is writable among threads.
***
##### Brief on external synchronization of shared_ptr and other not fully internal synchronized types:
So if main function initializes one shared_ptr and starts threads and threads just read from the shared_ptr, no external synchronization is needed.
If the shared_ptr is modified in the future, then it is a writable shared object and external synchronization is needed.
***
##### How to determinate a class should be fully synchronized:
1. It's a writable object.
2. It's shared among threads.

Classes that meet all the requirements is usually used for either inter-thread communication or synchronization.



[jekyll-docs]: http://jekyllrb.com/docs/home
[jekyll-gh]:   https://github.com/jekyll/jekyll
[jekyll-talk]: https://talk.jekyllrb.com/
