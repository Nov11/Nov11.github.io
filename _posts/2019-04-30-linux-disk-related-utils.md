---
layout: post
title:  "linux network configurations"
date:   2019-04-14 17:03:00 +0800
categories: jekyll update
---

configs:
diry_page config
https://lonesysadmin.net/2013/12/22/better-linux-disk-caching-performance-vm-dirty_ratio/

common tunning techniques:
https://www.percona.com/blog/2016/08/12/tuning-linux-for-mongodb/



tools:
hdparam : test read performance


proc:
 /sys/block/sda/queue/scheduler : disk task scheduler

 /sys/block/sda/queue/read_ahead_kb  : read ahead

 /proc/sys/vm/nr_pdflush_threads : number of pdflush thread running

 /proc/sys/vm/dirty_expire_centisecs : if data has stayed longer than this, flush it

 /proc/sys/vm/dirty_writeback_centisecs : pdflush running interval. it can be disabled

 /proc/sys/vm/dirty_background_ratio : pdflush kicks in to flush out dirty pages

 /proc/sys/vm/dirty_ratio : application write blocks if dirty memory ratio reach this limit



greate resources:
* hdparam -t(cached:no disk access) and -T(buffered: just disk access) : https://www.unix.com/unix-for-dummies-questions-and-answers/163209-difference-between-buffered-disk-reads-cached-reads.html
* over commit : https://www.kernel.org/doc/Documentation/vm/overcommit-accounting
* linux config : https://www.kernel.org/doc/Documentation/sysctl/vm.txt




[jekyll-docs]: http://jekyllrb.com/docs/home
[jekyll-gh]:   https://github.com/jekyll/jekyll
[jekyll-talk]: https://talk.jekyllrb.com/
