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
#include <atomic>
using namespace std;

// 对资源进行引用计数的类
template<typename T>
class RefCnt {
public:
	RefCnt(T* ptr = nullptr): mptr(ptr){
		if (mptr != nullptr) {
			// mcount = 1;
			mcount.store(1); // 引用计数安全 atomic_int CAS
		}
	}
	void addRef() { mcount++; } // 添加资源的引用计数
	// int delRef() { return --mcount; }
	int delRef() { --mcount; return mcount.load(); } // 引用计数安全 atomic_int CAS
private:
	T* mptr;
	// int mcount;
	atomic<int> mcount; // 引用计数安全 atomic_int CAS
};

// 智能指针  保证能做到资源的自动释放！！！
// 利用栈上的对象出作用域自动析构的特征，来做到资源的自动释放！
// CSmartPtr<int>* p  = new CSmartPtr<int>(new int); delete p;
template<typename T>
class CSmartPtr { // shared_ptr  weak_ptr
public:
	CSmartPtr(T* ptr = nullptr) :mptr(ptr) {
		mpRefCnt = new RefCnt<T>(mptr);
	}
	~CSmartPtr() {
		if(mpRefCnt->delRef() == 0){
			delete mptr;
			mptr = nullptr;
		}
	}
	T& operator *() { return *mptr; }
	T* operator ->() { return mptr; }
	CSmartPtr(const CSmartPtr<T>& src)
		: mptr(src.mptr), mpRefCnt(src.mpRefCnt){
		if (mptr != nullptr)
			mpRefCnt->addRef();
	}
	CSmartPtr<T>& operator=(const CSmartPtr<T>& src) {
		if (this == &src)
			return *this;
		if (mpRefCnt->delRef() == 0) {
			delete mptr;
		}

		mptr = src.mptr;
		mpRefCnt = src.mpRefCnt;
		mpRefCnt->addRef();
		return *this;

	}
private:
	T* mptr;           // 指向资源的指针
	RefCnt<T>* mpRefCnt;  // 指向该资源引用计数对象的指针
};
int main() {

	/*
	带引用计数的智能指针shared_ptr和weak_ptr
	带引用计数：多个智能指针可以管理同一个资源
	带引用计数：给每一个对象资源，匹配一个引用计数；
	智能指针 => 使用资源的时候 => 引用计数+1
	智能指针 => 不使用资源的时候 => 引用计数-1 => !=0 0资源释放了
	*/

	CSmartPtr<int> ptr1(new int);
	CSmartPtr<int> ptr2(ptr1);
	CSmartPtr<int> ptr3;
	ptr3 = ptr2;

	*ptr2 = 20;
	cout << *ptr2 << " " << *ptr3 << endl;



	return 0;
}
