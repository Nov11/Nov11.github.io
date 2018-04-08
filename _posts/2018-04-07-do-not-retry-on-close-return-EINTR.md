---
layout: post
title:  "Do not retry on close returning EINTR "
date:   2018-04-07 22:47:59 +0800
categories: jekyll update
---

TL;DR No retry on close failure on Linux.
Use close$NOCANCEL on Mac OS if needed.

* no need for linux 
[stackoverflow](https://unix.stackexchange.com/questions/219148/is-the-return-value-1-of-the-function-socket-close-method-possible)
* man page
[man page](http://man7.org/linux/man-pages/man2/close.2.html)
* what close interface should be 
[behavior](shttp://austingroupbugs.net/view.php?id=529)
* full explaination:
[EINTER and thread cancellation](https://github.com/wahern/cqueues/issues/56)

[jekyll-docs]: http://jekyllrb.com/docs/home
[jekyll-gh]:   https://github.com/jekyll/jekyll
[jekyll-talk]: https://talk.jekyllrb.com/
