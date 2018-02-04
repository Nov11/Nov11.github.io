---
layout: post
title:  "Notes on : Ansel Sermersheim “Multithreading is the answer. What is the question? (part 2 of 2)”(CppCon 2017)"
date:   2018-02-01 22:39:00 +0800
categories: jekyll update
---

### How to review multithreaded code ?
#### Example 1
```c++
ComplicatedObject *createObject(int param1, double param2){
    ComplicatedObject* retval;
    
    retval = new ComplicatedObject();
    retval->doSomething(param1);
    retval->somethingElse(param2);
    
    return retval;
}
```
Defects:
* using raw pointer
* exception safety(using new)

#### Example 2
```c++
class MyCache{
    public:
        voidd insert(std::string key, ComplicatedObject* element);
        ComplicatedObject* lookup(std::string key) const;
    private:
        std::map<std::string, ComplicatedObject*> m_cache;
        std::shared_timed_mutex m_cacheMutex;
};

ComplicatedObject* MyClass::lookup(std::string key) const{
    std::shared_lock<std::shared_timed_mutex> lock(m_cacheMutex);
    
    return m_cache[key];
}
```
Defects:
* Unclean about who is responsible to delete objects in the map.
* Possibly create a new entry in map when looking up no-exist item and holding read lock at the same time.
 This results in undefined behavior.

Not done yet.......