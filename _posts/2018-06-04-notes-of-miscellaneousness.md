---
layout: post
title:  "let's put those pieces back again. mainly about java"
date:   2018-05-29 23:55:59 +0800
categories: jekyll update
---

1. interrupt exception handling
    * if current method is meaningful when marked with interrupted exception, say
    it cannot do what's intend,
    mark it and throw the exception up leve
    * if not, deal with it. typically catch it and mark interrupted. this exp
    may be cause by other thread informing current one to exist. mark it interrupted 
    so that upper level functions might figure this out and take proper action.
2. exception hierarchy
    throwable-> exception / error(not checked)
    exception -> runtime exception(not checked) / checked exception
3. template variable def(PECS : producer extends, consumer super)
    * wanna write to something: List<? super T> (the code which is being ritten works as producer)
    * wanna read from it : List<? extends T> (the code which is being written works as consumer)
    * wanna exactly something : List<T>
4. completablefuture will be run in the thread call complete on the first stage
    if the completablefuture is created by new and chained with lots of later stages, the thread in which
    complete is call on the first stage will execute all the stages of the chain.
5. thenApply, thenAccept, thenCompose
    * thenApply get previous result and make one result, passing down the chain
    * thenAccpet get previous result and consume it. return nothing
    * thenCompose is like flatmap, returns the completablefuture the parameter function returns 
   and also consumes previous stage's output
6. IntStream. when use its output as int, use boxed
7. During bean creation state, if you're using function annotated with @Bean, Spring creates each object if the function name is different. In another word, if you got two function with the same name, one object will be created but the other one will not. This may lead to obfuscating error message cause the bean creation method sits here sound and tight, but you are kept informing no such bean found.
8. thrift maven plugin may not support '-r' option. It comes to you when include a file not ending with '.thrift'. 
9. 'find' command with '+' will use all the input as one parameter.
10. Sadly, if the thrift files doesn't properly contains a package name, compilation will fail anyway. maven cannot find classes that do not have a package statement in them. Set up package names if you're dealing with cross platform thrift practice.
11. interruptedexception. Deal with it : 1)rethrow, or 2)Thread.currentThread().interrupt(). 
12. thrift does not output null value in json by default. if that's what you need, you need a new protocal class and customized write method for a target schema. it's clumsy anyway.
13. thrift protocol could be modified to implement a feature that ommit some field names in the structure. field ids can be used as path to that field and current path can be checked before writing struct.
14. use ```-XX:-OmitStackTraceInFastThrow``` if you find exceptions like NullPointerException are printed without stack trace.
15. This is not a solution but a thought. Let's talk about tracing within a single app through thread boundard and deep level of call stack. guess thread local is not always sufficent and for call back like completable future, it's hard to maintain the parent trace within every step of executaion stages. What should I do if I wanna detailed trace of an executaion?
16. Invoking get on CompletableFuture with negative timeout will result in timeout exception.
17. static field and static initialzation block obeys later sees former rule. cannot refer to a static field in static block if the block shows up before the field.
18. slow rpc calls stalled threads in a pool and new tasks may be rejected. I saw one practical example today.
19. resouce leak such as hashwheeltimer may eventally cause an out of memory exception and terminate the jvm? not having the hard evidence, but this seems to be reasonable.
---------------------------------------
1. delete backward with reverse_iterator in a for loop. 
   ```c++
   set<int> s;
   // some initalization
   for(auto riter = s.rbegin(); riter != s.rend();){
      s.erase(--riter.base());
   }
   or
   for(auto riter = s.rbegin(); riter != s.rend();){
      riter = decltype(riter){s.erase(std::next(riter).base());
      // or riter = decltype(riter){s.erase((++riter).base())};
   }
   ```
   
   
[jekyll-docs]: http://jekyllrb.com/docs/home
[jekyll-gh]:   https://github.com/jekyll/jekyll
[jekyll-talk]: https://talk.jekyllrb.com/
