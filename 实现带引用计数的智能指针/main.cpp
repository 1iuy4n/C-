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
#include <atomic>
using namespace std;

// ����Դ�������ü�������
template<typename T>
class RefCnt {
public:
	RefCnt(T* ptr = nullptr): mptr(ptr){
		if (mptr != nullptr) {
			// mcount = 1;
			mcount.store(1); // ���ü�����ȫ atomic_int CAS
		}
	}
	void addRef() { mcount++; } // �����Դ�����ü���
	// int delRef() { return --mcount; }
	int delRef() { --mcount; return mcount.load(); } // ���ü�����ȫ atomic_int CAS
private:
	T* mptr;
	// int mcount;
	atomic<int> mcount; // ���ü�����ȫ atomic_int CAS
};

// ����ָ��  ��֤��������Դ���Զ��ͷţ�����
// ����ջ�ϵĶ�����������Զ���������������������Դ���Զ��ͷţ�
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
	T* mptr;           // ָ����Դ��ָ��
	RefCnt<T>* mpRefCnt;  // ָ�����Դ���ü��������ָ��
};
int main() {

	/*
	�����ü���������ָ��shared_ptr��weak_ptr
	�����ü������������ָ����Թ���ͬһ����Դ
	�����ü�������ÿһ��������Դ��ƥ��һ�����ü�����
	����ָ�� => ʹ����Դ��ʱ�� => ���ü���+1
	����ָ�� => ��ʹ����Դ��ʱ�� => ���ü���-1 => !=0 0��Դ�ͷ���
	*/

	CSmartPtr<int> ptr1(new int);
	CSmartPtr<int> ptr2(ptr1);
	CSmartPtr<int> ptr3;
	ptr3 = ptr2;

	*ptr2 = 20;
	cout << *ptr2 << " " << *ptr3 << endl;



	return 0;
}
