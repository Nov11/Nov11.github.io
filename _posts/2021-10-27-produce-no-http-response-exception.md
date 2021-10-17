---
layout: post
title:  "one way to produce NoHttpResponseException"
date:   2021-10-17 20:31:00 +0800
------

Having encountered NoHttpResponseException when using Apache Http Client, I did some search on the Internet about this. Although the root cause is not confirmed as lack of logs from online service, it might be helpful for people who want to produce this exception on their own.

The key point is pause execution just after client socket connected and shutdown server. Then let client run. On receiving RST from server, the client throws exceptions that NoHttpResponse comes first;

Traffic Packets:
![pic1](https://raw.githubusercontent.com/Nov11/Nov11.github.io/master/pics/produce-nohttpresponseexception/pcap.png)
Exception log:
![pic1](https://raw.githubusercontent.com/Nov11/Nov11.github.io/master/pics/produce-nohttpresponseexception/exception.png)
Line of client code to pause on:
![pic1](https://raw.githubusercontent.com/Nov11/Nov11.github.io/master/pics/produce-nohttpresponseexception/httpclient.png)


[jekyll-docs]: http://jekyllrb.com/docs/home
[jekyll-gh]:   https://github.com/jekyll/jekyll
[jekyll-talk]: https://talk.jekyllrb.com/
