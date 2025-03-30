/*
����ָ�����
�Լ�ʵ������ָ��
�������ü���������ָ��auto_ptr,scoped_ptr,unique_ptr
�����ü���������ָ��shared_ptr,weak_ptr
����ָ��Ľ������ã�ѭ�����ã�����
���̷߳��ʹ����������
�Զ���ɾ����
*/

#include <iostream>
#include <memory>
#include <functional>
using namespace std;

// ����ָ��  ��֤��������Դ���Զ��ͷţ�����
// ����ջ�ϵĶ�����������Զ���������������������Դ���Զ��ͷţ�
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

// ʹ�� std::function ����ɾ��������
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
	Deleting 000001E995EE8240  // ��һ�η���� int �����ڵڶ��θ�ֵʱ���ͷ�
	Deleting 000001E995EE8280  // �ڶ��� int �����ڳ������ʱ���ͷ�
	*/
	ptr1 = getSmartPtr(); // ��ȷ��ɾ��������һ�£������ƶ���ֵ



	/*
	�������ü���������ָ��
	��ô���ǳ�������⣡����
	auto_ptr:C++������
	C++11�±�׼��
	scoped_ptr
	scoped_ptr(const scoped_ptr<T>&) = delete;
	scoped_ptr<T>& operator=(const scoped_ptr<T>&) = delete;

	�Ƽ�ʹ�ã�
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

	��ô���ǳ�������⣡����

	std::move => C++11 ��ֵ���� std::move�õ���ǰ��������ֵ����
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
	// ���Ƽ�ʹ��auto_ptr, vector<auto_ptr<int> > vec1; vec2(vec1);


	return 0;
}
