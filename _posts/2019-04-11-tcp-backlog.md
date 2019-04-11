---
layout: post
title:  "redis tcp-backlog"
date:   2019-04-11 21:42:00 +0800
categories: jekyll update
---

Clients cannot connect to redis instance if redis instance is blocking due to AOF and at the same time configed with small tcp-backlog compare to incoming connections.

Here's how to reproduce this:
1. setup redis server with tcp-backlog of 1. 
2. connect to it wit redisson client

below is the screen shot of wireshark:
![pic1](https://raw.githubusercontent.com/Nov11/Nov11.github.io/master/assets/pics/2019-04-11/packet.png)

this is the exception redisson thrown:
![pic1](https://raw.githubusercontent.com/Nov11/Nov11.github.io/master/assets/pics/2019-04-11/exception.png)

[jekyll-docs]: http://jekyllrb.com/docs/home
[jekyll-gh]:   https://github.com/jekyll/jekyll
[jekyll-talk]: https://talk.jekyllrb.com/
