#include <iostream>
#include <type_traits>
using namespace std;

class Base{};
class Child :public Base{};
class Child2 :public Child{};

class A{};


template<class T,
     class DummyType=
		 class  std::enable_if<
		 std::is_base_of<Base, T>::value,std::true_type>::type>
class MyTemplate {
};
int main()
{
	MyTemplate<Child> a;//ok
	MyTemplate<Child2> b;//ok

	//MyTemplate<int> c; compile error
	//MyTemplate<A> d; compile error
}