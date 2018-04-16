---
layout: post
title:  "about override private virtual fucntions in C++"
date:   2018-04-16 23:14:59 +0800
categories: jekyll update
---

See this usage in MySQL's handler class. Find it really weird when you got knowledge of C++ & Java.


About private virtual functions: [C++ FAQs](https://isocpp.org/wiki/faq/strange-inheritance#private-virtuals)


'private' doesn't stop you from override a virtual function. And as it means, derived class cannot call base class's 
private function as usual. Private virtual function is useful implementing template pattern.


In short, if you wanna a custom method in derived class and do not want it to show up in class interface and you do not want
to provide a reusable base code, mark it private pure virtual.  

[jekyll-docs]: http://jekyllrb.com/docs/home
[jekyll-gh]:   https://github.com/jekyll/jekyll
[jekyll-talk]: https://talk.jekyllrb.com/
