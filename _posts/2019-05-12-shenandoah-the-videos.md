---
layout: post
title:  "about shenandoah"
date:   2019-05-12 19:49:00 +0800
categories: jekyll update
---

collecting resources of this garbage collector.

###about this speech : Shenandoah GC: The Garbage Collector That Could : Aleksey Shipilev

https://vimeo.com/289626122

||young|old|
|serial parallel|copy(STW)|mark & compact(STW)|
|cms|copy(STW)|init mark(STW) & concurrent mark & finish mark(STW) & Concurrent swap|
|G1|copy(STW)|init mark(STW) & concurrent mark & finish mark(STW) & compact(STW)|
|shenandoah|init mark(STW) & concurrent mark & finish mark(STW) & Concurrent compact|

latency = alpha * heapSize * MemoryRef(stw) * memoryAccessLatency

Shenandoah is regionalized GC. Similar to G1. Not generational by default. Not tracking refs into a region.



[jekyll-docs]: http://jekyllrb.com/docs/home
[jekyll-gh]:   https://github.com/jekyll/jekyll
[jekyll-talk]: https://talk.jekyllrb.com/
