---
layout: post
title:  "mongodb ttl index is not a drop-in replacement for redis's setex"
date:   2019-04-22 20:50:00 +0800
categories: jekyll update
---
mongodb uses ttl index to expire documents. if you wanna use mongodb as a replacement for redis in some latency not critical scenarios, delete expired documents by yourself other than rely on ttl index. constantly updated fields that represents expire time is just a single field in redis, but a indexed field in mongodb. that means modifying the field in mongodb will result in much more book keeping works to maintain the index structure. and also this slows down the overall performance. deleteMany with a filter condition on expiring time point can remove all the expired documents easily. even with ttl background thread, often a full table scan is inevitable. so there's no point scan through using a cursor and delete documents in batches. the modified index's impact on performance can be seen if a index is created on that field. actually the background ttl thread/removing actions do not have that significant imfluence on performance (latency, to be presice).

[jekyll-docs]: http://jekyllrb.com/docs/home
[jekyll-gh]:   https://github.com/jekyll/jekyll
[jekyll-talk]: https://talk.jekyllrb.com/
