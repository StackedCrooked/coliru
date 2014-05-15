#include <iostream>
#include <algorithm>
#include<functional>
#include<vector>


using namespace std;
using namespace std::placeholders;


struct MyType
{
    int _val;
	MyType(int a) : _val(a){}
};


int main()
{
	vector<MyType> vec{ 1, 2, 4, 5 };

	auto m = std::max_element(vec.begin(), vec.end(), 
                              bind(less<int>(), bind(&MyType::_val, _1), bind(&MyType::_val, _2)));

	std::cout << m->_val << endl;

	return 0;
}
