---
layout: post
title:  "Wireless card driver installation on fresh installed Ubuntu 18.04LTS"
date:   2018-10-02 15:44:59 +0800
categories: jekyll update
---

Let's talk about how to install wireless card driver on a fresh ubuntu installation.

Assume you get no wire connected to your machine but using wireless card to access Internet and you just installed a fresh new Ubuntu 18.04.
If wireless card is not recognized by Ubuntu 18.04 LTS desktop installation process, you have to install it by yourself.
The problem may seems a little bit 'recursive' : if I cannot connect to Internet, how can I get a driver? if I cannot get
a driver, how can I connect to Internet? Well, there's some other way.....

The driver must be download and compile from source. This is for sure.

Download driver from this repo: https://git.kernel.org/pub/scm/linux/kernel/git/iwlwifi/backport-iwlwifi.git.
Better download a zip/tarball other than plan git clone if you're doing this in windows. Or you have to deal with 'CR's in many config files.
If you're using a Windows on the same machine, it'll be easy to access the downloaded file in Ubuntu. Otherwise, guess a flash disk is needed.


When it comes to compiling the code, packages referred to by 'build-essentials' are needed.
1.The apt could be set to use the ISO image as apt source by editing /etc/apt/source.list(I think the path is stable from Ubuntu version 16 to 18) and putting this inside:
`deb file:///[the dir you mount your image, better without space] bionic main restrict`.
Then update apt source. Run `sudo apt install build-essentials`.
2.Run `sudo make defconfig-iwlwifi-public`. It needs a sudo on my OS.
3.Run `sed -i 's/CPTCFG_IWLMVM_VENDOR_CMDS=y/# CPTCFG_IWLMVM_VENDOR_CMDS is not set/' .config`. This comments out one option. I don't know what's the option really does.
4.make->make install->reboot

On the next boot, wireless icon should show itself on the status bar.

May the driver be included in the next dist update.

references:
[driver installation](https://askubuntu.com/questions/1016903/alienware-17-r4-ubuntu-16-04-wifi-driver)

[jekyll-docs]: http://jekyllrb.com/docs/home
[jekyll-gh]:   https://github.com/jekyll/jekyll
[jekyll-talk]: https://talk.jekyllrb.com/
