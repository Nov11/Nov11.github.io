---
layout: post
title:  "Using JVisualVm on a remote host"
date:   2018-10-12 19:39:00 +0800
categories: jekyll update
---
VisualVM -> Connect to remote jvm 

1.config jvm to support remote jmx connection
using maven as building tool, so I add these to ‘MAVEN_OPTS’
```
-Dcom.sun.management.jmxremote=true 
-Dcom.sun.management.jmxremote.port=50001 
-Dcom.sun.management.jmxremote.ssl=false 
-Dcom.sun.management.jmxremote.local.only=false 
-Djava.rmi.server.hostname=localhost 
-Dcom.sun.management.jmxremote.authenticate=false 
-Dcom.sun.management.jmxremote.rmi.port=50002
```
These options can be checked with jinfo.


2.establish ssh tunnels to server
```
ssh -Nf -L50002:server_name:50002(you will need this. This is actual remote visualvm is talking to.)
ssh -Nf -L50001:server_name:50001(rmi register)
```
```
Local 50001->remote 50001
Local 50002->remote 50002
```
3.connect in visual vm
add jmx connection without ssl

here you go

MISC:

* I don’t have root privilege, so jstasd is not a applicable approach. And I haven’t  tried that.
* In the above example, two tunnels for each of the two ports are needed. I haven’t tried to specify jmxremote.port/jmxremote.rmi.port to the same port. 
* But, all one can do with a visualvm is sampling. Profiling is not possible as it’s not supported.
* Even if web app is started on local machine, profiler doesn’t work as I expected. It show nothing from beginning of Cpu profiling  to the end.

Guess I need other tools or print timeline by hand using tracing.

References:
* https://theholyjava.wordpress.com/2012/09/21/visualvm-monitoring-remote-jvm-over-ssh-jmx-or-not/

* https://stackoverflow.com/questions/1609961/visualvm-over-ssh

* https://dzone.com/articles/java-memory-and-cpu-monitoring-tools-and-technique

* https://stackoverflow.com/questions/41041819/how-to-get-profile-tab-in-visualvm-cross-platform

[jekyll-docs]: http://jekyllrb.com/docs/home
[jekyll-gh]:   https://github.com/jekyll/jekyll
[jekyll-talk]: https://talk.jekyllrb.com/
