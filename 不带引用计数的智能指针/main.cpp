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
#include <memory>
#include <functional>
using namespace std;

// 智能指针  保证能做到资源的自动释放！！！
// 利用栈上的对象出作用域自动析构的特征，来做到资源的自动释放！
// CSmartPtr<int>* p  = new CSmartPtr<int>(new int); delete p;
template<typename T>
class CSmartPtr {
public:
	CSmartPtr(T* ptr = nullptr) :mptr(ptr) {}
	CSmartPtr(const CSmartPtr<T>& src) {
		mptr = new T(*src.mptr);
	}
	~CSmartPtr() {
		delete mptr;
		mptr = nullptr;
	}
	T& operator *() { return *mptr; }
	T* operator ->() { return mptr; }
private:
	T* mptr;
};

// 使用 std::function 定义删除器类型
using Deleter = std::function<void(int*)>;
Deleter deleter = [](int* p) {
	std::cout << "Deleting " << p << std::endl;
	delete p; 
};

std::unique_ptr<int, Deleter> getSmartPtr() {
	return std::unique_ptr<int, Deleter>(new int(), deleter);
}


int main() {
	std::unique_ptr<int, Deleter> ptr1 = getSmartPtr();
	/*
	Deleting 000001E995EE8240  // 第一次分配的 int 对象在第二次赋值时被释放
	Deleting 000001E995EE8280  // 第二个 int 对象在程序结束时被释放
	*/
	ptr1 = getSmartPtr(); // 正确：删除器类型一致，触发移动赋值



	/*
	不带引用计数的智能指针
	怎么解决浅拷贝问题！！！
	auto_ptr:C++库里面
	C++11新标准：
	scoped_ptr
	scoped_ptr(const scoped_ptr<T>&) = delete;
	scoped_ptr<T>& operator=(const scoped_ptr<T>&) = delete;

	推荐使用：
	unique_ptr
	unique_ptr(const unique_ptr<T>&) = delete;
	unique_ptr<T>& operator=(const unique_ptr<T>&) = delete;

	unique_ptr(unique_ptr<T>&& src)
	unique_pre<T>& operator=(unique_ptr<T>&& src)

	template<typename T>
	unique_ptr<T> getSmartPtr(){
		unique_ptr<T> ptr(new T());
		return ptr;
	}

	unique_ptr<int> ptr1 = getSmartPtr<int>();
	ptr1 = getSmartPtr<int>();

	怎么解决浅拷贝问题！！！

	std::move => C++11 右值引用 std::move得到当前变量的右值类型
	*/
	//unique_ptr<int> ptr1(new int);
	//unique_ptr<int> ptr2(std::move(ptr1));


	// CSmartPtr<int> p1(new int);
	// CSmartPtr<int> p2(p1);
	// p1 p2 => new int
	// *p1 = 20;
	// *p2 = 30;

	// auto_ptr<int> ptr1(new int);
	// auto_ptr<int> ptr2(ptr1);
	// *ptr2 = 20;
	// cout << *ptr1 << endl;
	// 不推荐使用auto_ptr, vector<auto_ptr<int> > vec1; vec2(vec1);


	return 0;
}
