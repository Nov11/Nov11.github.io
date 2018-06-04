---
layout: post
title:  "mockito usage note"
date:   2018-05-29 23:55:59 +0800
categories: jekyll update
---

1. If a class is mocked and has method A calling method B and method B has a mock stub.
Configure method A with callrealmethod or it will not call mocked method B but returns null value. This could be frustrating.
2. careful when using eq. e.g. specifying a long value by eq(233) will not make the mock work but lead to frustration.
[jekyll-docs]: http://jekyllrb.com/docs/home
[jekyll-gh]:   https://github.com/jekyll/jekyll
[jekyll-talk]: https://talk.jekyllrb.com/
