---
layout: post
title:  "let's put those pieces back again. mainly about java"
date:   2018-05-29 23:55:59 +0800
categories: jekyll update
---

1. interrupt exception handling
    * if current method is meaningful when marked with interrupted exception, say
    it cannot do what's intend,
    mark it and throw the exception up leve
    * if not, deal with it. typically catch it and mark interrupted. this exp
    may be cause by other thread informing current one to exist. mark it interrupted 
    so that upper level functions might figure this out and take proper action.
2. exception hierarchy
    throwable-> exception / error(not checked)
    exception -> runtime exception(not checked) / checked exception
3. template variable def
    * wanna write to something: List<? super T>
    * wanna read from it : List<? extends T>
    * wanna exactly something : List<T>
4. completablefuture will be run in the thread call complete on the first stage
    if the completablefuture is created by new and chained with lots of later stages, the thread in which
    complete is call on the first stage will execute all the stages of the chain.
[jekyll-docs]: http://jekyllrb.com/docs/home
[jekyll-gh]:   https://github.com/jekyll/jekyll
[jekyll-talk]: https://talk.jekyllrb.com/
