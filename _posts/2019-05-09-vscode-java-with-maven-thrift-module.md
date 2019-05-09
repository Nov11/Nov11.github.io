---
layout: post
title:  "vscode java with multiple module maven project that generates thrift classes"
date:   2019-05-09 17:49:00 +0800
categories: jekyll update
---

vscode supports remote editing/debuging. SSH to a remote machine in vscode and no rsync/git push/pull is need to transfer locate updates to development machine.

A little modification is needed if maven project contains modules that compiles from thrift and some kind of IDL into a dependency jar.

* open .classpath file in that module which contains the IDLs
* make sure the generated source files are under a html element like this:
```
<classpathentry kind="src" path="target/generated-sources/thrift"/>
```

clean java language server workspace might be helpful. but it will reset .classpath file.

debug / launch is not what I expect as it seems not to be a mvn command. got to use an old fashion shell script to start the application. debug / attach works and needs nothing then a debug port, since your application and vscode are running on the same machine.

the .classpath config blocks me for quite a while. hope this post will help.

[jekyll-docs]: http://jekyllrb.com/docs/home
[jekyll-gh]:   https://github.com/jekyll/jekyll
[jekyll-talk]: https://talk.jekyllrb.com/
