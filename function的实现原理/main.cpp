#include <iostream>
#include <typeinfo>
#include <string>
#include <functional>
using namespace std;
/*
function函数对象类型的实现原理
*/
void hello(string str) { cout << str << endl; }
int sum(int a, int b) { return a + b; }
/****************************************/
template<typename Fty>
class myfunction{};

/*
template<typename R, typename A1>
class myfunction<R(A1)> {
public:
	using PFUNC1 = R(*)(A1);
	myfunction(PFUNC1 pfunc): _pfunc(pfunc){}
	R operator()(A1 arg) {
		return _pfunc(arg); // hello(arg)
	}
private:
	PFUNC1 _pfunc;
};

template<typename R, typename A1, typename A2>
class myfunction<R(A1, A2)> {
public:
	using PFUNC1 = R(*)(A1, A2);
	myfunction(PFUNC1 pfunc) : _pfunc(pfunc) {}
	R operator()(A1 arg1, A2 arg2) {
		return _pfunc(arg1, arg2); // sum(arg1, arg2)
	}
private:
	PFUNC1 _pfunc;
};
*/

template<typename R, typename... A>
class myfunction<R(A...)> {
public:
	using PFUNC1 = R(*)(A...);
	myfunction(PFUNC1 pfunc) : _pfunc(pfunc) {}
	R operator()(A... arg) {
		return _pfunc(arg...); // hello(arg)
	}
private:
	PFUNC1 _pfunc;
};
int main() {
	//function<void(string)> func1 = hello;
	myfunction<void(string)> func1 = hello;
	func1("hello world!"); // func1.operator()("hello world!")
	myfunction<int(int, int) > func2(sum);
	cout << func2(10, 20) << endl;
	return 0;
}