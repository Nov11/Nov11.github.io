#include <iostream>
#include <vector> 

struct X
{
	X() { std::cout << "constructed\n"; }
	X(const X&) { std::cout << "copied\n"; }
	X(X&&) { std::cout << "moved\n"; }
	~X() { std::cout << "destructed\n"; }
};

void func() {}
std::vector<X> Get(int a)
{
	// copy elision from tempory object to 'temp', omit copy and move constructor
	std::vector<X> temp;// = std::vector<X>(1);
	std::vector<X> t2;
	std::vector<X> t23;
	func();
	if (a > 2) { t2.push_back(X()); return t2; }
	else if (a < 0) { return temp; }
	else { t23.push_back(X()); t23.push_back(X()); return t23; }
	//return temp; // NRVO temp to returned 
}

std::vector<X> b() {
	std::vector<X> tmp;
	std::cout << "in func b" << std::endl;
	//return std::move(tmp);
	return tmp;
}

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
int main()
{
	//std::vector<X> v = Get(1113);
	//std::cout << "lalal" << std::endl;
	//std::vector<X> v1 = b();
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
	//X& rett = foo2();
}

// Output

/*
constructed
destructed
*/

//作者：蓝色
//链接：https ://www.zhihu.com/question/29511959/answer/44617879
//来源：知乎
//著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

//some modification is done base on code wriiten by 蓝色.
//hint:
//use this to see funcions called without copy/move elision: g++ -fno-elide-constructors -std=c++11 a.cpp