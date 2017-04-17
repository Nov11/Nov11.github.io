---
layout: post
title:  "C++11 : RVO and std::move"
date:   2017-04-17 15:31 +0800
categories: jekyll update
---
***
#### Conditions that RVO takes place([standard](#standard) 12.8 section 31):

>When certain criteria are met, an implementation is allowed to omit the copy/move construction of a class
object, even if the constructor selected for the copy/move operation and/or the destructor for the object
have side effects. In such cases, the implementation treats the source and target of the omitted copy/move
operation as simply two different ways of referring to the same object, and the destruction of that object
occurs at the later of the times when the two objects would have been destroyed without the optimization.126
This elision of copy/move operations, called copy elision, is permitted in the following circumstances (which
may be combined to eliminate multiple copies):

>— in a return statement in a function with a class return type, when the expression is the name of a
non-volatile automatic object (other than a function or catch-clause parameter) with the same cvunqualified
type as the function return type, the copy/move operation can be omitted by constructing
the automatic object directly into the function’s return value

>— in a throw-expression, when the operand is the name of a non-volatile automatic object (other than a
function or catch-clause parameter) whose scope does not extend beyond the end of the innermost
enclosing try-block (if there is one), the copy/move operation from the operand to the exception
object (15.1) can be omitted by constructing the automatic object directly into the exception object

>— when a temporary class object that has not been bound to a reference (12.2) would be copied/moved
to a class object with the same cv-unqualified type, the copy/move operation can be omitted by
constructing the temporary object directly into the target of the omitted copy/move

>— when the exception-declaration of an exception handler (Clause 15) declares an object of the same type
(except for cv-qualification) as the exception object (15.1), the copy/move operation can be omitted
by treating the exception-declaration as an alias for the exception object if the meaning of the program
will be unchanged except for the execution of constructors and destructors for the object declared by
the exception-declaration.

***
#### Conditions that implicit move takes place([standard](#standard) 12.8 section 32):
>When the criteria for elision of a copy operation are met or would be met save for the fact that the source
 object is a function parameter, and the object to be copied is designated by an lvalue, overload resolution to
 select the constructor for the copy is first performed as if the object were designated by an rvalue. If overload
 resolution fails, or if the type of the first parameter of the selected constructor is not an rvalue reference to
 the object’s type (possibly cv-qualified), overload resolution is performed again, considering the object as an
 lvalue. [Note: This two-stage overload resolution must be performed regardless of whether copy elision will
 occur. It determines the constructor to be called if elision is not performed, and the selected constructor
 must be accessible even if the call is elided. — end note]

*** 
#### When to use std::move in return statement?
* return parameters not passed by value(i.e. passed by T& or T&&).
* it is known that rvo will not take place and move is needed(i.e. return statement needs type conversion)

#### When not to use std::move?
* returning one local variable that can be copy/move elided. Or std::move prevents this.
* intention is to copy reference parameter to return value
 
***
#### About std::forward and std::move
* forward always needs a template parameter but move doesn't 
* std::move do a cast from parameter to its corresponding rvalue ref
* forward returns rvalue ref when param is rvalue, returns lvalue if param is lvalue
* forward is mostly used in perfect forwarding with T&& as param and forward it to inner functions


***
Links related to this topic that I found useful:  

[when to use move in return statement](http://stackoverflow.com/questions/14856344/when-should-stdmove-be-used-on-a-function-return-value)  
[similar to the one above](http://stackoverflow.com/questions/17473753/c11-return-value-optimization-or-move)  
[std::move int return statement prevents rvo](http://stackoverflow.com/questions/19267408/why-does-stdmove-prevent-rvo)  
[one intro to rvo and move](https://www.ibm.com/developerworks/community/blogs/5894415f-be62-4bc0-81c5-3956e82276f3/entry/RVO_V_S_std_move?lang=en)  
<a name="standard"></a>
[the c++11 standard](https://isocpp.org/files/papers/N3690.pdf)     

*** 
If some experiments is needed, this code may be useful.
[get the code]({{ site.url }}/assets/code/2017-04-17/a.cpp)  
functions:
```$xslt
X foo() {
	X tmp;
	return tmp;
}

X foo2() {
	X tmp;
	return std::move(tmp);
}

X foo3(X& param) {
	return param;
}
X foo4(X& param) {
	return std::move(param);
}

X foo5(X param) {
	return param;
}

X foo6(X param) {
	return std::move(param);
}

X foo7(X&& param) {
	return param;
}

X foo8(X&& param) {
	return std::move(param);
}
```
test by:
```$xslt
{	std::cout << "new test" << std::endl;
	X ret = foo();
	}
	{
		std::cout << "new test2" << std::endl;
		X ret2 = foo2();
	}
	X param;
	{
		std::cout << "new test3" << std::endl;

		X ret3 = foo3(param);
	}
	{
		std::cout << "new test4" << std::endl;
		X ret4 = foo4(param);
	}
	{
		std::cout << "new test5" << std::endl;
		X ret4 = foo5(param);
	}
	{
		std::cout << "new test6" << std::endl;
		X ret4 = foo6(param);
	}
	{
		std::cout << "new test7" << std::endl;
		X ret4 = foo7(std::move(param));
	}
	{
		std::cout << "new test8" << std::endl;
		X ret4 = foo8(std::move(param));
	}
```

elide-constructors:  
![withelison]({{ site.url }}/assets/pics/2017-04-17/withelision.PNG)  
no-elide-constructors:  
![withoutelison]({{ site.url }}/assets/pics/2017-04-17/withoutelision.PNG)


[jekyll-docs]: http://jekyllrb.com/docs/home
[jekyll-gh]:   https://github.com/jekyll/jekyll
[jekyll-talk]: https://talk.jekyllrb.com/
