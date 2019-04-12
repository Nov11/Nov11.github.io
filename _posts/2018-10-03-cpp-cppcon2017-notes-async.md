---
layout: post
title:  "The Asynchronous C++ Parallel Programming Model"
date:   2018-10-03 16:25:59 +0800
categories: jekyll update
---

[The Asynchronous C++ Parallel Programming Model](https://www.youtube.com/watch?v=js-e8xAMd1s)

In my words, use future as return value and chain dependencies by chaining futures.

Guidelines to write efficient application.

* parallel as much as humanly possible
    * 4 aspects that restrict parallelism(SLOW)
        1. Starvation: insufficient concurrent workload to maintain high utilization of resources.
        2. Latency: Time-distance delay of remote resources access and services.
        3. Overhead: Work for management of parallel actions and resources on critical path which are not necessary in sequential program.
        4. Waiting: Delay due to lack of availability of oversubscribed shared resource(contention resolution).
* use programming environment that embraces SLOW
* allow for your grain size to be variable
* oversubscribe and balance adaptively

The challenge
* Expose asynchrony but without exposing additional concurrency
* Make data dependency explicit, hide notion of thread/communication
* Provide manageable paradigms for handling parallelism

Proposed solutions
* Asynchronous programming model
    * objects interacting with async function calls(remote calls are sent as active messages)
    * futures are used to represent data dependencies in async execution flow. benefits:
        * synchronized with producer threads transparently
        * no notion of threads
        * allows for composition of async operations
        * turns concurrency into parallelism

Async communication

What this talk is mainly about?
I think the summary will be : use future as your function return value and chain them to express dependencies.

[jekyll-docs]: http://jekyllrb.com/docs/home
[jekyll-gh]:   https://github.com/jekyll/jekyll
[jekyll-talk]: https://talk.jekyllrb.com/
