---
layout: post
title:  "customized tf op"
date:   2021-10-19 20:31:00 +0800
categories: jekyll update
---

* follow this guide ![guide](https://github.com/tensorflow/custom-op):
    * docker pull tensorflow/tensorflow:custom-op-ubuntu16 (download docker image)
    * clone https://github.com/tensorflow/custom-op (clone code repositery)
    * docker run -it -v custom-op:/custom-op tensorflow/tensorflow:custom-op-ubuntu16 (launch docker img with dir mapping)
    * ./configure.sh (run this inside /custom-op in the image)
    * bazel build build_pip_pkg (build wheel)
    * bazel-bin/build_pip_pkg artifacts (build wheel)
    * pip install tensorflow==2.4 (run this before pip install artifacs/xxx.wheel)
    * pip install artifacts/xxx
    * python3 -c "import tensorflow as tf;import tensorflow_zero_out;print(tensorflow_zero_out.zero_out([[1,2], [3,4]]))" (run test)

Traffic Packets:
![pic1](https://raw.githubusercontent.com/Nov11/Nov11.github.io/master/pics/produce-nohttpresponseexception/pcap.png)
Exception log:
![pic1](https://raw.githubusercontent.com/Nov11/Nov11.github.io/master/pics/produce-nohttpresponseexception/exception.png)
Line of client code to pause on:
![pic1](https://raw.githubusercontent.com/Nov11/Nov11.github.io/master/pics/produce-nohttpresponseexception/httpclient.png)


[jekyll-docs]: http://jekyllrb.com/docs/home
[jekyll-gh]:   https://github.com/jekyll/jekyll
[jekyll-talk]: https://talk.jekyllrb.com/
