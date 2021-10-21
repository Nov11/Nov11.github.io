---
layout: post
title:  "following offical customized tf op tutorial"
date:   2021-10-19 20:31:00 +0800
categories: jekyll update
---

* follow this guide [offical guide](https://github.com/tensorflow/custom-op):
    * docker pull tensorflow/tensorflow:custom-op-ubuntu16 (download docker image)
    * clone https://github.com/tensorflow/custom-op (clone code repositery)
    * docker run -it -v custom-op:/custom-op tensorflow/tensorflow:custom-op-ubuntu16 (launch docker img with dir mapping)
    * ./configure.sh (run this inside /custom-op in the image)
    * bazel build build_pip_pkg (build wheel)
    * bazel-bin/build_pip_pkg artifacts (build wheel)
    * pip install tensorflow==2.4 (run this before pip install artifacs/xxx.wheel. the container has tensorflow-cpu 2.4 but no tensorflow installed)
    * pip install artifacts/xxx
    * python3 -c "import tensorflow as tf;import tensorflow_zero_out;print(tensorflow_zero_out.zero_out([[1,2], [3,4]]))" (run test. do not executing this inside custom-op directory. using any other directory will be fine)

* tips:
    * running pip is equivalent to running pip3 inside container
    * install tensorflow manully inside container. it seems that tensorflow 2.6 does not work with the docker image. use version 2.4 might help.
    * test script should be execute outside custom-op directory
    * add a new user with `useradd xxx -m` might help if you want clean tmp files generated inside directory.



Traffic Packets:
![pic1](https://raw.githubusercontent.com/Nov11/Nov11.github.io/master/pics/produce-nohttpresponseexception/pcap.png)
Exception log:
![pic1](https://raw.githubusercontent.com/Nov11/Nov11.github.io/master/pics/produce-nohttpresponseexception/exception.png)
Line of client code to pause on:
![pic1](https://raw.githubusercontent.com/Nov11/Nov11.github.io/master/pics/produce-nohttpresponseexception/httpclient.png)


[jekyll-docs]: http://jekyllrb.com/docs/home
[jekyll-gh]:   https://github.com/jekyll/jekyll
[jekyll-talk]: https://talk.jekyllrb.com/
