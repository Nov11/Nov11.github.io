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
#### about php client
I did this on php script. It should be the same to use it in a web page. This saves the effort of restart apache2 server again and again.
##### windows
* PHP version
  * I tried PHP 5. It didn't work due to can find a file already in include path. And I read some posts on the error. It needs to include a dll in configuration to solve the problem. But I cannot find compiled dll on pecl and I don't even want to compile under windows. PHP7.2 works. It has compiled php_grpc.dll on pecl site.
  * I haven't figure out how to get a grpc_php_plugin without compile the huge grpc repositery which I cannot succeed for sure. I get the files by specify additional command lines to VS's generator. It works.
  * Composter helps me a lot. I'm a newbee and just want to produce a client-server communication between C++ server and a php client. If you happens to be the same, just use it. It is bundled in PhpStorm which is certainly another greate tool.
  * Don't try pecl in command line with PHP5. I watsted hours doing that before I found that I cannot get prebuilt grpc by pecl.
* the whole picture
  * two ways: build from source / use the prebuilt dll etc
  * build from source code is hard. I tried but failed.
  * PHP5 lacks prebuilt support for some package. (like php_grpc.dll)
* the componets you need
  * (serialization / deserializtion)protoc : compiler converts proto configuration to language specific files
  * (network communication)grpc plugin : generate stubs for you. 
  * (runtime)runtime library : .ddl, .so 
  * (common base component) grpc
  * for php usage, plugin sits on top of grpc and use protobuf. configure php with runtime library and grpc is ready to go
##### linux(ubuntu 16, tried but not fully succeeded in build the client)
* I don't want to bulid from source. gRPC has lots of packages on linux platforms. 
* On ubuntu 16, php7 is listed in the default apt repositery. no need to pick php5.
* install grpc/protobuf may still leave you in front of header not found error. use composter install may solve the prolem.
* It seems that there's no way to get grpc php plugin without compiling the source code.

### This could be a solution to converting a C/S application into a B/S application without changing but wrapping the connection client.
