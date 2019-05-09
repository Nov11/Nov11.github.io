---
layout: post
title:  "redis tcp-backlog"
date:   2019-04-11 21:42:00 +0800
categories: jekyll update
---

Clients cannot connect to redis instance if redis instance is blocking due to AOF and at the same time configed with small tcp-backlog compare to incoming connections.

with '/proc/sys/net/ipv4/tcp_abort_on_overflow' == 1, server will not send sync/ack back to client immediately, which leads to client side timeout.

Here's how to reproduce this:
1. setup redis server with tcp-backlog of 1. 
2. connect to it wit redisson client

below is the screen shot of wireshark:
![pic1](https://raw.githubusercontent.com/Nov11/Nov11.github.io/master/assets/pics/2019-04-11/packet.png)

this is the exception redisson thrown:
![pic1](https://raw.githubusercontent.com/Nov11/Nov11.github.io/master/assets/pics/2019-04-11/exception.png)

resource:
* http://veithen.io/2014/01/01/how-tcp-backlog-works-in-linux.html

By the way, when server received ack from client but accept queue is full and if /proc/sys/net/ipv4/tcp_abort_on_overflow == 1, a RST will be sent. Or the ack is ignored and server resend SYNC/ACK to /proc/sys/net/ipv4/tcp_synack_retries the socket after timeout.

[jekyll-docs]: http://jekyllrb.com/docs/home
[jekyll-gh]:   https://github.com/jekyll/jekyll
[jekyll-talk]: https://talk.jekyllrb.com/
