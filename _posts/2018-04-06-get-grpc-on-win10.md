---
layout: post
title:  "Get gRPC on Windows 10"
date:   2018-04-06 05:28:00 +0800
categories: jekyll update
---

## Let's talk about how to install gRPC on Windows 10
#### the normal way
I tried but failed. By the way, submodules could be downloaded individually. And there's no need to use git submodule update --init --recursive and wait long long time.
No need to mention the 30k commits of gRPC history. I download a zip file of the repositery and download submodules by hand with 'depth' specified.
It takes less time then the way provided on install.md. But these will not get you anywhere because the cmake errors during configuration.
#### the vcpkg
##### hint
* install english language pack of vs 2017. or vcpkg won't find vs.
* speicify VCPKG_DEFAULT_TRIPLET = x64-windows if you wanna x64 package in default
* no need to install cmake forehead, cause vcpkg won't identify it even it resides in your PATH.
* no need to install the perl package listed on gRPC install.md or yasm. vcpkg will get strawberry perl & nasm.
#### complains
I shouldn't have expeced cross platform open source project gives greate support on windows. It's a pain to build open source project in windows.
Got to say that Vcpkg is a good package management tool. It saves me lots of efforts
#### alternative
I searched and knew this repositery : https://github.com/plasticbox/grpc-windows. But I haven't try it. This may be helpful.
