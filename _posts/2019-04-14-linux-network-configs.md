---
layout: post
title:  "linux network configurations"
date:   2019-04-14 17:03:00 +0800
categories: jekyll update
---
|config|meaning|
|:-|:-|
|/proc/sys/net/ipv4/tcp_abort_on_overflow  | 1: send RST if accept queue is full default 0|
|/proc/sys/net/ipv4/tcp_synack_retries | number of tcp reties|
|/proc/sys/net/ipv4/tcp_max_syn_backlog| max length of the queue contains all incomplete socket system wide|


greate resources:
* tcp-backlog : http://veithen.io/2014/01/01/how-tcp-backlog-works-in-linux.html but in fact, linux does not send sync/ack back. see my post on tcp-backlog
[jekyll-docs]: http://jekyllrb.com/docs/home
[jekyll-gh]:   https://github.com/jekyll/jekyll
[jekyll-talk]: https://talk.jekyllrb.com/
