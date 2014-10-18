#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <iterator>
#include <numeric>
#include <functional>

class A
{
public:
    void foo(int a){ std::cout << a; }
};
int main()
{
	A a;
	std::vector<int> v{ 1, 2, 3 };
	std::for_each(v.begin(), v.end(), std::bind1st(std::mem_fun(&A::foo), &a));
}