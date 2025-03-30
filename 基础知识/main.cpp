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
using namespace std;

// ����ָ��  ��֤��������Դ���Զ��ͷţ�����
// ����ջ�ϵĶ�����������Զ���������������������Դ���Զ��ͷţ�
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

	// data��    heap��    stack��
	int* p = new int(10);

	*p = 30;
	if (false)
		return -1;

	delete p;

	return 0;
}