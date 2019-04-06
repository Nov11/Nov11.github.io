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
54. after 10+ wait time out during maven repositery deployment, I finally succeed. don't hang on this. whenever running into this, try it later.
55. aspectj compiler produces hasAspect/aspectOf methods in aspect class. if these methods doesn't show up, NoSuchMethodException awaits in runtime. to ensure this generation, make aspject plugin runs last. commenting out maven-compiler-plugin might be helpful if you're running in a multimodule maven project and maven-compiler-plugin is set in parent pom. the order in the same submodule pom seems to make no difference. and also, this might not be deterministic if you have maven-compiler first and aspecjt second. It works sometime, fails sometime.
56. remove files with only comments inside. these will be treated as stale by maven-compiler-plugin and trig compilation every time, which will not trigger ajc compile. bet you won't like this.
57. it's not that effective to reduce cpu usage by caching serialized binary of large objects and reusing them. this might performs well when total cpu usage is low. but decrease when overall cpu usage is high, which means many operations other than serialization is being processed by cpu. this caching enhancement can be done by aop the thrift generated write method.
58. when running grafana & graphite via docker on a server, to set the ip address of graphite to grafana, get it from docker0 interface by docker network inspect. it's not the same as running the on the local machine, in which case localhost is the right hostname.
59. `nc -l localhost port ` will establish a server listening on 127.0.0.1. When connections are made from another machine, they won't be able to reach this port. Use `nc -l port` instead and an entry like '0.0.0.0:7890' will show up after calling netstat.
60. On mac, nc localhost port usually issue an IPV6 connection rather than IPV4. thus nothing shows up in 'nc -lu port'. use `nc -4u localhost port` instead.
61. when it comes to forwarding udp through ssh tunnel, use socat other than nc with fifo. like this : client side `socat udp4-recvfrom:8125,reuseaddr,fork tcp:localhost:18125`(udp4-listen doesn't work on my machine. not knowing why.), server side `socat tcp4-listen:18125,reuseaddr,fork udp:localhost:8125`. theses will make many connections. certainly not good for the long run. but still better than nc with fifos. this might stash datagram into two tcp packet which  on the server side makes it hard to reconstruct reasonable packets from them.
62. setting cache value with a timestamp and then the value can be use as a fall back if the value expired and remote rpc fails. 
    ```
    #!/bin/bash
    rm /tmp/ttt
    mkfifo /tmp/ttt
    nc -l 18125 < /tmp/ttt |tee /dev/tty |  nc -u localhost 8125 > /tmp/ttt
    
    #!/bin/bash
    rm /tmp/ttt
    mkfifo /tmp/ttt
    nc -kl4u localhost 8125 < /tmp/ttt | tee /dev/tty | nc localhost 18125 > /tmp/ttt
    ```
63. actually directbuffer will be freed when not referenced. this is done via a phantom reference field inside the ref object. during cleaning phase, the off heap memory will be freed.
64. avro does not support backward compatability. 
65. sonarqube depends on JaCoCo which does not support multi-module maven project directly. A fresh new aggregation module is needed to generate aggregate report of all modules that shoud be counint for coverages and be linted. 'report-aggregate' should be used in that module. And do reference all the deepest modules in the dependency tree in that aggregate module.
66. redis `memory usage keyname` command show overall memory consumption of a given key. `debug object keyname` shows some details as well.
67. mongodb use wiredtiger's btree as default storage engine. lsm is configurable when creating a new collection but not in mongodb.conf.
68. ping from within a container which connects to bridge network to another host is not gonna work. use host network or use virtual machine. it's might be possible in the future release. but not for now.
69. running pmm server in a docker and pmm client on another host, collecting metrics are problems cannot be solved for the moment. use virtualbox to run pmm server in ova instead.
70. -o GatewayPorts=yes to allow access from docker container other than just localhost
71. ssh -4 to force ipv4 connection. or else ipv6 might be troublesome.
72.  number > /proc/sys/vm/drop_caches.1:clear pagecache, 2:clear directories and inodes, 3:both 1 and 2. test disk write/read throughput with these commands :`dd if=/dev/zero of=diskbench bs=1M count=1024 conv=fdatasync` , `echo 3 | sudo tee /proc/sys/vm/drop_caches` , `dd if=diskbench of=/dev/null bs=1M count=1024` 
73. AOF might make redis not responding to new coming connections. unbelievable. when a file is been called on fsync, another write call on the same file will block the calling thread. although redis uses a seperate thread doing fsync, and make write into a temp buffer while the thread does not finish. redis call write on the file if the fsync doesn't finish in 2 seconds. I think AOF on a slave which exists in a cluster might be eligible of turned off. In that if a single slave is still alive, the state is perserved.
74. do enable rdb if running a master-slave replication. or even if sentinel is active, a flash restart of master without persistence might not be perceved by sentinel. this results in empty master. and the master will erase everything on its slave. if running replication, config master with some sort of persistence to avoid data loss.
75. if redis is blocking in aof write, tcp connections can still be established provided that backlog is not exceeded, which is unlikely in most cases. but redis works in a request response way, so if it is blocked, it will not be able to answer request. client & sentinels may find their commands timeout or ping / auth command not being answered. in case of auth, one looks like it cannot be auth. in case of sentinel probing, it looks like a network partition occured. I think rdb should be enabled on master node and no AOF should be turned on on any nodes in the cluster.
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
