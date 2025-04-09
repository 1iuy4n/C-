#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <ctime>

using namespace std;

/*
绑定器和函数对象operator()

1.C++ STL中的绑定器
bind1st : operator()的第一个形参变量绑定成一个确定的值
bind2nd : operator()的第二个形参变量绑定成一个确定的值

2.C++11从Boost库中引入了bind绑定器和function函数对象机制

3.lambda表达式 底层依赖函数对象的机制实现的
*/
template<typename Container>
void showContainer(Container& con) {
	typename Container::iterator it = con.begin();
	for (; it != con.end(); ++it) {
		cout << *it << " ";
	}
	cout << endl;
}
int main() {
	vector<int> vec;
	srand(time(nullptr));
	for (int i = 0; i < 20; ++i) {
		vec.push_back(rand() % 100 + 1);
	}

	showContainer<vector<int> >(vec);
	sort(vec.begin(), vec.end()); // 默认从小到大排序
	showContainer<vector<int> >(vec);

	// greater 二元函数对象
	sort(vec.begin(), vec.end(), greater<int>());  // 大到小排序
	showContainer<vector<int> >(vec);

	/* 把70按顺序插入到vec容器当中  找第一个小于70的数字
	operator() (const T& val)
	greater  a>b
	less     a<b
	绑定器 + 二元函数对象 => 一元函数对象
	bind1st: + greater bool operator()(70, const _Ty& _Right)
	bind2nd: + less bool operator()(const _Ty& _Left, 70)
	*/

	//auto it1 = find_if(vec.begin(), vec.end(), bind1st(greater<int>(), 70));
	auto it1 = find_if(vec.begin(), vec.end(), bind2nd(less<int>(), 70));
	if (it1 != vec.end()) {
		vec.insert(it1, 70);
	}
	showContainer(vec);


	return 0;
}