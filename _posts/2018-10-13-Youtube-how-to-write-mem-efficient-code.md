---
layout: post
title:  "How to Write Memory-Efficient Java Code"
date:   2018-10-14 18:4:00 +0800
categories: jekyll update
---

### memory usage of Java code
#### on 32bit platform, one Integer object is 128bit, 4 times the size of int (32 bits)
object layout
on 32bit platform
|type|0|32|64|96|128|
|-|-|-|-|-|-|
|java object Integer 10|class pointer to in class|flags(hash code etc)|lock(flat lock/ pointer to inflated monitor)|int value| 
|java array with single value 10|class pointer to in class|flags(hash code etc)|lock(flat lock/ pointer to inflated monitor)|size|int value|
        
on 64bit platform, reference type doubles its size
|type|0|64|128|192|224|256|
|-|-|-|-|-|-|-|
|java object Integer 10|class pointer to in class|flags(hash code etc)|lock(flat lock/ pointer to inflated monitor)|int value| 
|java array with single value 10|class pointer to in class|flags(hash code etc)|lock(flat lock/ pointer to inflated monitor)|size|size|int value|

**auto boxed types consumes more memory than primitive type**

#### migrating from 32 to 64 bit platform will generally increase Java heap usage by 70% and native heap usage by 90%
Provided memory size is within 32GB, Compressed reference use relative addressing in 64 Java heaps.
Object meta and object references become 32bits. This reduce Java heap usage but not native heap usage.
And memory usage 64bit Java app is the same as 32bit version.
** do not disable UseCompressedOops if you're using memory less than 32 GB **

#### simple object like String
Let's make HEAD=class pointer + flags + lock. One java.lang.String will be like this: HEADER|hash|count|offset|value|.
 value points to another object of type char[]: HEADER|size|chars|. 
** use String with one char inside is a waste of memory ** 

### minimize creation of new objects
when object allocation and reclamation happen temporary objects created in calculation / transformation / business transaction etc.
GC is a tax on performance. It's typically up to 10% of overhead.
 
#### String concatenation
```Java
String s1 = "s1";
String s2 = "s2";
String s3 = s1 + s2;

those above will be converted into(video says this could be verified in javad, which I didn't try):
String s3 = new StringBuilder(String.valueOf(s1)).append(s2).build();
```
* String s1, s2 each has two objects created, one String and a char[] it points to. (4 objects)
* StringBuilder and its char[].(2 objects)
* String s3 has two objects.(2 objects)

in the end, objects other than s3 will be candidates for gc. that's 6 objects.

Java optimizes String usage by interning String. Unique Strings are stored in a pool. String objects can just be pointer to one of them.

**Allocation and reclamation can be reduced using caches. And caches reduce overall memory usage.**

### choose the right collection type
Collections have different memory overhead. Basically ArrayList < LinkedList < HashTable < HashMap < HashSet.
Collections expand automatically but do not shrinks automatically. 

### analyze your application for memory inefficiency
the eclipse tool is not applicable in IDEA. So just leave it there.
Memory analyze on collection fill rate and incoming reference may lead developer to origin of lower usage collection creation spots.

Roughly speaking, some hints on saving memory usage on collections.
1. lazy creation. create a collection until you really need it.
2. improve occupation of a collection. do not create one but only insert one entry into it.
3. create with appropriate size if possible. this could save some empty entries.
4. avoid memory expansion like 2x in most cases. e.g. use 17MB of 32MB allocated memory.
5. if one dropped many items, the collection may need to be resize. collections will not shrink.


the video : https://www.youtube.com/watch?v=f2aNWtt0QRo

reference:
(compressed reference for OOP(ordinary object pointer)) [https://docs.oracle.com/javase/7/docs/technotes/guides/vm/performance-enhancements-7.html]


[jekyll-docs]: http://jekyllrb.com/docs/home
[jekyll-gh]:   https://github.com/jekyll/jekyll
[jekyll-talk]: https://talk.jekyllrb.com/
