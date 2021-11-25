---
layout: post
title:  "tips on building python from source to use with tensorflow recommender addons"
date:   2021-11-25 23:31:00 +0800
categories: jekyll update
---


* tips:
    * install bz2 : ```sudo apt-get install libbz2-dev```
    * install sqlite : ```sudo apt install libsqlite3-dev```
    * download and extract python 3.8 source tar ball then run : ```./configure --prefix=/usr/local/python3.8 --enable-optimizations```
    * ```sudo make install```
    * use newly installed python ```/usr/local/python3.8/bin/python3```



[jekyll-docs]: http://jekyllrb.com/docs/home
[jekyll-gh]:   https://github.com/jekyll/jekyll
[jekyll-talk]: https://talk.jekyllrb.com/
