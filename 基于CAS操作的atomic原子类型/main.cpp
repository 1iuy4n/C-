#include <iostream>
#include <thread>
#include <list>
#include <atomic> // 包含了很多原子类型
using namespace std;

/*
C++11
窗口卖票  int count=100;
lock_guard<std::mutex> guard(mtx);
count++;

lock_guard<std::mutex> guard(mtx);
count--;

互斥锁是比较重的，临界区代码做的事情稍稍复杂，多
系统理论：CAS来保证上面++ --操作的原子特性就足够了，无锁操作
          exchange/swap   无锁队列 => CAS来实现的
*/

volatile std::atomic_bool isReady = false;
volatile std::atomic_int numCount = 0;

void task(){
	while (!isReady) {
		std::this_thread::yield(); // 线程让出当前的CPU时间片，等待下一次调度
	}

	for (int i = 0; i < 100; ++i) {
		numCount++;
	}
}
int main() {

	list<std::thread> tlist;
	for (int i = 0; i < 10; ++i) {
		tlist.push_back(std::thread(task));
	}
	std::this_thread::sleep_for(std::chrono::seconds(3));
	isReady = true;
	for (std::thread& t : tlist) {
		t.join();
	}
	cout << "numCount:" << numCount << endl;

	return 0;
}