#include <iostream>
#include <functional>

using namespace std;

class Foo{
public:
    int value;
};


template <typename T>
void test(
	const std::function<T()>&,
	const std::function<void(const T&)>&)
{
	std::cout << "func 1" << std::endl;
}

template <typename T>
void test(
	const std::function<T()>&,
	const std::function<void(Foo*)>&)
{
	std::cout << "func 2" << std::endl;
}

int main()
{
	std::function<void(const int&)> intFunc = [](const int&){};
	std::function<void(Foo*)> fooFunc = [](Foo*){};
	test<int>([](){ return 0; }, intFunc);
	test<int>([](){ return 0; }, fooFunc);

	test<int>([](){ return 0; }, [](Foo*){}); // C2668 here. Why?
	return 0;
}
