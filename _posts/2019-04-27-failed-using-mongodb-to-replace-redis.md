---
layout: post
title:  "failed using mongodb to replace redis"
date:   2019-04-27 13:00:00 +0800
categories: jekyll update
---

There is a redis instance accepting 70,000+ read & write commands per second.
Write operations make up 1/4, the other is read operations.

Mongodb instance is deploied with many other redis instanes on the same machine.
The db takes 50GB memory(many other memory is taken by redis instances) and using the whole RAID 10 disk.
The data is kept for 2 days, with possibliy that one documents expire time be perlonged. It takes about 64GB disk space, which is larger than memory that wiredtiger can use.

Write operations can be taken on a single instance. The original storage is serialized binary in redis. And when a message comes in, a read-modify-write procedure is taken. This limits through put on slower dbs that use disks. Instead, store the original info as fields in mongodb, the read-modify-write can be changed into a single update, which can be collected into a bulk update to save the RTT and increase through put. This acutally reduces the cpu previous method needs from 40 to 2. This makes about 8k update requests to the db instance.

But a single server cannot handle all the read request. After turning this into a replica with three nodes to provide high availibility and specify secondary prefer as read preference, a situation that cpu usage go high like 3 times of availible cores from a normal load of half of cpu cores did happen. The io has been saturated. Response time went wild. Sudden increase on network input may be the cause(It seemed like a network problem quickly fixed after it occured). This happened after one replica falled behind with others. In addition, a third consumer would make background dirty page flusher overwhelmed. Increasing eviction thread number raise machine cpu load, which is not an option. Even it's possible, this deployment is fragile and easily fails when writing work load grows. 

There is only the three machine with limited memory that I can use. Turning this into sharding will sacrifice high availibility. I think this is the farthest I can possibliy reach. Sad, but this is the reality.


[jekyll-docs]: http://jekyllrb.com/docs/home
[jekyll-gh]:   https://github.com/jekyll/jekyll
[jekyll-talk]: https://talk.jekyllrb.com/
