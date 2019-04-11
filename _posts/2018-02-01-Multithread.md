---
layout: post
title:  "Notes on : Ansel Sermersheim “Multithreading is the answer. What is the question? (part 1 of 2)”(CppCon 2017)"
date:   2018-02-01 17:02:00 +0800
categories: jekyll update
---
## Section I (old fashion introduction)
### Why is multithreading complicated?
#### Facts:
* Same terms are used in different scenarios which may be confusing in communication.
* One race condition may reduce to a crash.
* It is quite easy to write code with memory leak.
* Random crashes hardly can be produced during tests but occur in production.

Don't forcefully apply multithreading to current problem unless it's a must.

#### Terminology
* Race condition: In cpp term, two accesses to same location of memory and at least one of them is a write operation.
This results in undefined behavior. 
* Fiber : light weight threads not scheduled OS. Only interrupted by calling yield and no two fibers run at the same time.
* Green Thread: User space thread.

## Section II (on methodology)
### When to use multithreading?
* Tasks can be split intuitively into independent processing steps.(embarrassing parallel, I think)
* A problem where each step has a clear input and output.
* Dealing with CPU bounded problem. i.e. computation intensive.
* Continuous access to a large read-only data set.
* Processing a stream of large data files.
### When multithreading must be used?
* Single thread performance is unacceptable.
* Workload cannot be anticipated.
* Manage concurrent access to multiple resources.

## Section III (examples)
### Multithreading analogy 
### A (shares nothing)
* Two chef working independently. (<-thread)
* Two knives.(local variable)
* Goal : make 50 salads.
* Solution : each chef makes 25 salads.

```c++
std::thread chef1(
    [](){
        for(int i = 0; i < 25; i++){
            makeFruitSalads();
        }
    }
);
//same for chef2
std::thread chef2(...);

chef1.join();
chef2.join();

```
### B (one shared variable, using mutex)
* Two chef working independently.(<-thread)
* Two knives.(local variable)
* One Oven.(shared resource)
* Goal : make 50 apple pies.
* Solution : each chef makes 25 pies.

```c++
Oven oven;
std::mutex oven_mtx;
std::thread chef1([&oven_mtx, &oven]()
    {
        for(int i = 0; i < 25; i++){
            Pie pie;
            pie.makeCrust();
            pie.putApplesInPie();
            std::local_guard<std::mutex> guard(oven_mtx);
            oven.bakePie(pie, temp, time);
        }
    }
);
//same as above. 
std::thread chef2(...);
chef1.join();
chef2.join();
```
### C (same as B, but solved in sync data structure by transferring owner ship)
* Two chef working independently.(<-thread)
* Two knives.(local variable)
* One Oven.(shared resource)
* Goal : make 50 apple pies.
* Solution : one chef prepares pies, the other one bakes.

```c++
Oven oven;
threadsafe_queue<Pie> conveyor;

std::mutex oven_mtx;
std::thread chef1([&conveyor]()
    {
        for(int i = 0; i < 50; i++){
            Pie pie;
            pie.makeCrust();
            pie.putApplesInPie();
            //std::local_guard<std::mutex> guard(oven_mtx);
            //oven.bakePie(pie, temp, time);
            conveyor.queue(std::move(pie));
        }
    }
);

std::thread chef2([&conveyor, &oven]()
{
    for(int i = 0; i < 50; i++){
        auto pie = queue.dequeu();
        
        oven.baksPie(pie, temp, time);
    }
}
);
chef1.join();
chef2.join();
```
Shared data may result in race condition. 
If threads can pass data around, 
this can leverage the problem by transferring **owner ship**.
Pretty similar to stream line.
And also this applies a great point about multithreading in general: If you can make it somebody else's problem, do it.


### D (choice of work load for each thread)
* Two chef working independently.(<-thread)
* Two knives.(local variable)
* One Oven.(shared resource)
* Goal : make 25 fruit salads and 25 chicken salads.
* Solution : 
    * each chef makes a fruit salad, cleans up, and makes a chicken salads.
    * one chef makes 25 fruit salads, one makes 25 chicken salads.
    * chefs make 25 fruit salads together and switch to chicken salads when it's done.

### E (more complex example)
* Many resources: pizza oven, ice cream maker...
* Working tasks can arrive at any time for any resources.
* Solution: pandemonium

```c++
Oven oven;
std::mutex oven_mtx;
Oven pizzaOven;
std::mutex pizzaOven_mtx;
IceCreamMaker iceCreamMaker;
std::mutex iceCreamMake_mtx;

class Food{};
class Pizza{};
class ApplePie{};
class IceCream{};

void eat(Food && food){
    ...
}

using PatronTicket = std::future<std::unique_ptr<Food>>;
using ChefTicket = std::promise<std::unique_ptr<Food>>;

std::thread patron1([](){
    PatronTicket pizza = orderPizza();
    PatronTicket iceCream = orderIceCream();
    
    eat(pizza.get());
    eat(iceCream.get());
}
);

std::thread patron2([](){
    PatronTicket iceCream = orderIceCream();
    
    eat(iceCream.get());
}
);
class Order{...};
std::atomic<bool> working;
threadsafe_queue<Order> orderQueue;

std::thread chef1([&] (){
    while(working){
        Order next = orderQueue.dequeue();
        next.process();
    }
}
);
//basically the same as above
std::thread chef2(...);

PatronTicket orderPizza(){
    std::shared_ptr<ChefTicket> chefTicket = std::make_shared<ChefTicket>();
    PatronTicket ticket = chefTicket->get_future();
    
    Order order{[chefTicket](){
        std::unique_ptr<Pizza> pizza = std::make_unique<Pizza>();
        pizza->addSource();
        pizza->addCheese();
        std::lock_guard<std::mutex> guard(pizzaOven);
        pizza = pizzaOven.bake(std::move(pizza));
        chefTicket->set_value(std::move(pizza));
    });
    
    orderQueue.queue(std::move(order));
    return patronTicket;
}
//other ordering functions are similar   
```
hint:
* Unique_ptr prevents shared data as it is the only one that owns the resource. 
Preventing shared data does good to correctness of program.
* C++14 supports move in lambda's capture list. In that case, shared_ptr is not needed.
* Promise cannot be copied but its pointer can. We don't want to deal with raw pointer anyway.
 Shared_ptr provides same functionality as a pointer 
and also manages its life time by taking care of releasing memory. I think this is how to come up with this usage of shared_ptr and promise.

## Section IV
### Advice:
* Avoid too many active threads. 
    * Better be  one or two threads on single core.
    * Moving blocking calls to a separate thread.
* Reduce shared data.
    * Reduce the number and size of shared data.
    * (design)Reduce the number of parts in the system that have access to shared data to its minimal feasible one.
    * Read only shared data is good both for caching and reasoning program behaviors.

(There are code duplications which can be avoided in real practice but I'll just leave them as they are since they are just demos.)  
[source codes can be found here](http://download.copperspice.com/kitchensink/source/)