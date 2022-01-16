---
layout: post
title:  "install python rocksdb on ubuntu 16.04"
date:   2022-01-16 15:22:00 +0800
categories: jekyll update
---

it doesn't work even pip install succeeded

python-rocksdb requires rocksdb installed in the system.

* setup rocksdb in the system
  * clone rocksdb repositery: ```git clone git@github.com:facebook/rocksdb.git```
  * checkout v5.3.3. (master branch might not work with python-rocksdb due to incompatible code)
  * instal dependencies: ```sudo apt install install libsnappy-dev zlib1g-dev libbz2-dev libgflags-dev liblz4-dev``` 'liblz4-dev' is needed but it doesn't show up in `python-rocksdb` install guide. 
  * ```make shared_lib ```
  * ```sudo make install-shared INSTALL_PATH=/usr ```
* install `python-rocksdb`
  * ```pip install python-rocksdb```. is should run smoothly



[jekyll-docs]: http://jekyllrb.com/docs/home
[jekyll-gh]:   https://github.com/jekyll/jekyll
[jekyll-talk]: https://talk.jekyllrb.com/
