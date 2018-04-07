---
layout: post
title:  "In case you wanna start sth automatically"
date:   2017-11-23 18:40:54 +0800
categories: jekyll update
---

I'm talking about using systemd on Ubuntu 17.10. 
* write a config file in directory ```/usr/lib/systemd/system```. It's ok to create the last level directory. 
e.g.     


```
[Unit]
Description=license_server

[Service]
Type=simple
ExecStart=/home/****

[Install]
WantedBy=graphical.target

```
* run ```systemctl enable the_file_name```
* done

to check all config units :```systemctl list-units```
to see logs : ```systemctl status the_service_name```

It appears that if a console application is what you want to run, use simple as type, not forking.  
I found the explanation is not some how not what is means, well?  
As I'm using this on desktop, I choose graphical.target. Pick target according to your need.  

In case you wanna use a python script but encounter 'no ... module', check os.sys.path and use a export PYTHONPATH='missing one' before the script. This is useful if python script is install by pip.
