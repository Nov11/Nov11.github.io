---
layout: post
title:  "Notes on install thrift on Ubuntu 18.04"
date:   2018-10-17 00:50:00 +0800
categories: jekyll update
---

* 'configure' will tell you that it needs libcrypto. run this: 'sudo apt install libssl1.0-dev'. yes, libssl1.0-dev.
If libssl is installed, install libssl1.0-dev before running configure.
* If configure script doesn't detect java install path, install ant and try again. If you've got ant installed and still 
the script can not find java installtion, check config.log. If grepping 'java' from that file gives no error, just make && make install.
It turns out that installed thrift supports java.

not a very pleasant experience if you have to use this old thrift version.

[jekyll-docs]: http://jekyllrb.com/docs/home
[jekyll-gh]:   https://github.com/jekyll/jekyll
[jekyll-talk]: https://talk.jekyllrb.com/
