#include <vector>
#include <iostream>
#include <string>

template<class T>
class MyClass
{
public:
    void push_back(T&&)
	{
		std::cout << "in rvalue\n";
	}
	void push_back(const T&)
	{
		std::cout << "in lvalue\n";
	}
};
void foo(int&& val)
{
	MyClass<int> a;
	a.push_back(std::move(val));
	a.push_back(val);

}
int main()
{
	foo(1);

}