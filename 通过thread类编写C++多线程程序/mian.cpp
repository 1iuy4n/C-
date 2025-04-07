#include <iostream>
#include <thread>
#include <chrono>

/*
C++���Լ���Ķ��̱߳�� => ������Կ�ƽ̨ => ������Կ�ƽ̨ windows/linux/mac
thread/mutex/condition_variable
lock_quard/unique_lock
atmotic ԭ������ ����CAS������ԭ������ �̰߳�ȫ��
sleep_for

  C++���Բ��� thread
  windows           linux    strace  ./a.out
     |                |
createThread  pthread_create


�߳����ݣ�
һ. ��ô��������һ���߳�
std::thread����һ���̶߳��󣬴����߳�����Ҫ���̺߳����Ͳ�����
�߳��Զ�����

��. ���߳���ν���
���̺߳���������ɣ��߳̾ͽ�����

��. ���߳���δ������߳�
t.join : �ȴ�t�߳̽�������ǰ�̼߳�����������
t.detach : ��t�߳�����Ϊ�����̣߳����߳̽������������̽������������̶߳��Զ�������
*/
void threadHandle1(int time) {
	// �����߳�˯��time��
	std::this_thread::sleep_for(std::chrono::seconds(time));
	std::cout << "hello thread1!" << std::endl;
}
void threadHandle2(int time) {
	// �����߳�˯��time��
	std::this_thread::sleep_for(std::chrono::seconds(time));
	std::cout << "hello thread2!" << std::endl;
}
int main() {

	// ������һ���̶߳��� ����һ���̺߳��������߳̾Ϳ�ʼ������
	std::thread t1(threadHandle1, 2);
	std::thread t2(threadHandle2, 3);
	// ���̵߳ȴ����߳̽��������̼߳�����������
	t1.join();
	t2.join();
	// �����߳�����Ϊ�����߳�
	//t1.detach();

	std::cout << "main thread done!" << std::endl;

	// ���߳�������ɣ��鿴�����ǰ�����������δ������ɵ����߳�
	// ���̾ͻ��쳣��ֹ
	return 0;
}