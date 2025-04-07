#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue> // C++ STL���е������������̰߳�ȫ��
using namespace std;

/*
unique_lock  condition_variable
1.lock_guard �� unique_lock
2.condition_variable  wait��notify_all����
*/
std::mutex mtx; // pthread_mutex_t
std::condition_variable cv; // pthread_condition_t

int main() {
	/*
	֪ͨ��cv�ϵȴ����̣߳����������ˣ������ɻ��ˣ�
	������cv�ϵȴ����̣߳��յ�֪ͨ���ӵȴ�״̬ => ����״̬ => ��ȡ�������� => �̼߳�������ִ��
	*/
	cv.notify_all();

	// ����������ʹ���ڼ򵥵��ٽ�������εĻ�������У��������ں������ù�����
	//unique_lock<std::mutex> lck(mtx);
	//cv.wait(lck); // => #1.ʹ�߳̽���ȴ�״̬ #2.lck.unlock���԰�mtx���ͷŵ�

	// ���������ں����������ݻ��߷��ع�����
	// lock_guard<std::mutex> guard(mtx);

	//mtx.lock();
	//mtx.unlock();


	return 0;
}