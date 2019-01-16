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
20. lettuce must create different connections to use different codec. Is this real?
21. whenever a socket gets in fin_wait2, it can only receive FIN or it responses incoming packets with a RST.
22. bom should be used with scope->import. 
23. when creating bean with @Bean in spring configuration, spring use name as key when deciding which is the one to be wired in. duplicate bean method may be a unwelcomed source of frustration.
24. and also, in a large application package & component scan can be & should be organized carefully. forget this if not sub projects there will be that depend on some part of functions the module.
25. @ComponentScan is not tied with @Component annotation(@Controller/@Service/@Repositery/etc). it can be fed into context registration method. And inside import annotations as value, too.
26. Jetty will init servlets and then init connectors in the last step. check health handler will never serve a request until all servlet have been ready. It's ok to place it along spring mvc dispatcher.
27. JedisConnectionException unexpected end of stream/connection reset can be produced by obtain jedis object and hold it longer than redis server's timeout. if read get FIN first, unexpected result shows up. Otherwise connection reset shows up. When it comes to JedisConnectionException broken pipe, I've no idea how to produce it deterministically.
28. Never fool yourself by start a thread in thread factory of a pool. IllegalArgumentException is really ugly without reasonable information for trouble shotting.
29. If a field is to be serialized by thrift, do not set it directly. use setter instead. this could be a time killer. fxxk
30. lettuce's eval command returns long not integer. 
31. It's possible to have two charles certificate installed on one cellphone. Do add https proxied url in charles after certifacate is installed on the phone.
32. grafana stats interval may be larger than scale to interval. in that case, scaletosecond will produce average result. but summarize returns data points without averaging them. if data point sampling interval is smaller than scale to / summarize interval, they produce the same resilt. Whenever sampling interval is larger, use scaletosecond.
33. cut -d number_with_dash get fields numbered start from that column to the end. 
34. to use lettuce in master/slave mode, redis server needs to support ROLE command. Or lettuce will make reconnection attempt again and again.
35. script for inspecting cpu consuming java thread:
   ```bash
 #!/bin/bash
 V=`echo "obase=16; ${1}" | bc | tr '[A-Z]' '[a-z]'`
 echo ${V}
 ./jstack -l threadId | grep -C 20 nid=0x${V}

   ```
36. I stucked for a while when using gpg to generate key which is required by nexus. Here's what works for me. Use `gpg --full-gen-key` and use 4096 as key size.  Run `gpg2 --list-keys --keyid-format LONG` to get the key ID. And finaly run `gpg2 --keyserver hkp://pool.sks-keyservers.net --send-keys your key ID`. Since Ubuntu 18.04 comes with gpg of version 2, gpg / gpg2 is interchangable to my experience.
37. eclipse memory analyze tool is a great choice for large heap dump(above 4GB) analyze.
38. `X11UseLocalhost no` in sshd_config is needed when using X11 forwarding.
39. string' intern method may help if reusing constant string literal benifits. use with ` -XX:StringTableSize` to a larger value.
40. -XX:+UseStringDeduplication and -XX:StringDeduplicationAgeThreshold=3 might help if G1 GC is running. threshold defaults to 3.
41. apache bench mark tool's 'concurrency' means it will create users of that much and issue requests whenever one user gets its response. this is the meaning of the option.
42. I got kinda of hating G1 GC. Not sure but I'm encountering one Full GC problem slowly occuring after 4 hours of one deployment. Humongous GC might be the root cause.
43. `sudo apt-key adv --keyserver keyserver.ubuntu.com --recv-keys key-string` when you see apt complains that it cannot verify something due to missing this key-string. It's useful. 
44. if certain modules are loaded into kernel but docker still refuses to run and you're using a server with many routing rules, try this :`ip link add name docker0 type bridge ip addr add dev docker0 172.17.0.1/16`. it will save your from endless cycle of this kind : start docker! failed! start docker! failed!...   also, add `--iptables=false` to systemd config may rescue docker starting as well.
45. sshd might not read key files correctly because of mal configured locale. f**k
46. .tmux.conf with `set -g mode-mouse on` enables scrolling with mouse.
47. large objects the size of which is above 50% of region size might be a cause of Full GC. details not confirmed yet.
48. heapbytebuffer uses per thread cache of direct buffers with no number / size limitation. this may lead to continuous growing memory consumption.
49. options that relate to G1 GC. -XX:-ResizePLAB (said this may reduce CPU usage? not confirmed).-XX:+PerfDisableSharedMem(save jvm from waiting log flushing). -XX:+AlwaysPreTouch(not realy helpful).
50. internal memory showed in NMT is not the same as whole native memory. cause sometimes RES in top grows much larger than the size showed in 'internal memory'.
51. tried jemalloc but the graph / report do not provide a apparent clue. this is still a myth.
52. `--privileged` is needed if you wanna use perf inside a docker container.
53. jetty's queuedthreadpool has a rejection log which logs queueu status on rejection. but it's not that easy to grep since 'rejected' is likely widely used in loggings of one application.

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
