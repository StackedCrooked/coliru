#include <iostream>
#include <type_traits>
using namespace std;

class Base{};
class Child :public Base{};
class Child2 :public Child{};

class A{};

template<class T>
class MyTemplate{
    static_assert(std::is_base_of<Base, T>::value, "Wrong template parameter");
};
int main()
{
	MyTemplate<Child> a;//ok
	MyTemplate<Child2> b;//ok

	//MyTemplate<int> c; compile error
	//MyTemplate<A> d; compile error
}