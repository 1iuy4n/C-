#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <ctime>

using namespace std;

/*
�����ͺ�������operator()

1.C++ STL�еİ���
bind1st : operator()�ĵ�һ���βα����󶨳�һ��ȷ����ֵ
bind2nd : operator()�ĵڶ����βα����󶨳�һ��ȷ����ֵ

2.C++11��Boost����������bind������function�����������

3.lambda���ʽ �ײ�������������Ļ���ʵ�ֵ�
*/
template<typename Container>
void showContainer(Container& con) {
	typename Container::iterator it = con.begin();
	for (; it != con.end(); ++it) {
		cout << *it << " ";
	}
	cout << endl;
}

template<typename Iterator, typename Compare>
Iterator my_find_if(Iterator first, Iterator last, Compare comp) {
	for (; first != last; ++first) {
		if (comp(*first)) { // comp.operator()(*first)
			return first;
		}
	}
	return last;
}

template<typename Compare, typename T>
class _mybind1st { // ������һ�����������Ӧ��
public:
	_mybind1st(Compare comp, T val):_comp(comp), _val(val){}
	bool operator()(const T& second) {
		return _comp(_val, second); // greater
	}
private:
	Compare _comp;
	T _val;
};

// mybind1st(greater<int>(), 70)
template<typename Compare, typename T>
_mybind1st<Compare, T> mybind1st(Compare comp, const T& val) {
	// ֱ��ʹ�ú���ģ�壬�ô��ǣ����Խ������͵�����
	return _mybind1st<Compare, T>(comp, val);
}



int main() {
	vector<int> vec;
	srand(time(nullptr));
	for (int i = 0; i < 20; ++i) {
		vec.push_back(rand() % 100 + 1);
	}

	showContainer<vector<int> >(vec);
	sort(vec.begin(), vec.end()); // Ĭ�ϴ�С��������
	showContainer<vector<int> >(vec);

	// greater ��Ԫ��������
	sort(vec.begin(), vec.end(), greater<int>());  // ��С����
	showContainer<vector<int> >(vec);

	/* ��70��˳����뵽vec��������  �ҵ�һ��С��70������
	operator() (const T& val)
	greater  a>b
	less     a<b
	���� + ��Ԫ�������� => һԪ��������
	bind1st: + greater bool operator()(70, const _Ty& _Right)
	bind2nd: + less bool operator()(const _Ty& _Left, 70)
	*/

	//auto it1 = find_if(vec.begin(), vec.end(), bind1st(greater<int>(), 70));
	auto it1 = find_if(vec.begin(), vec.end(), mybind1st(greater<int>(), 70));
	//auto it1 = find_if(vec.begin(), vec.end(), bind2nd(less<int>(), 70));
	//auto it1 = my_find_if(vec.begin(), vec.end(), bind2nd(less<int>(), 70));
	if (it1 != vec.end()) {
		vec.insert(it1, 70);
	}
	showContainer(vec);


	return 0;
}