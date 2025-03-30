/*
智能指针介绍
自己实现智能指针
不带引用技术的智能指针auto_ptr,scoped_ptr,unique_ptr
带引用计数的智能指针shared_ptr,weak_ptr
智能指针的交叉引用（循环引用）问题
多线程访问共享对象问题
自定义删除器
*/

#include <iostream>
using namespace std;

// 智能指针  保证能做到资源的自动释放！！！
// 利用栈上的对象出作用域自动析构的特征，来做到资源的自动释放！
// CSmartPtr<int>* p  = new CSmartPtr<int>(new int); delete p;
template<typename T>
class CSmartPtr {
public:
	CSmartPtr(T* ptr = nullptr):mptr(ptr) {}
	~CSmartPtr() {
		delete mptr;
	}
	T& operator *() { return *mptr; }
	T* operator ->() { return mptr; }
private:
	T* mptr;
};
int main() {
	// int* p = new int;  *p  p->
	CSmartPtr<int> ptr1(new int);
	*ptr1 = 20;

	class Test {
	public:
		void test() { cout << "call Test::test"<<endl; }
	};
	CSmartPtr<Test> ptr2(new Test());
	// (ptr2.operator->())->test();
	ptr2->test(); // (*ptr2).test();

	return 0;
}

int main1() {

	// data段    heap段    stack段
	int* p = new int(10);

	*p = 30;
	if (false)
		return -1;

	delete p;

	return 0;
}