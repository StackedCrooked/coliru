#include <vector>
#include <iostream>
#include <string>

template<class T>
class MyClass
{
public:
    MyClass(std::initializer_list<T> l)
	{
		for (auto i : l)
			std::cout << i;
	}
};
template<class T, class...Args>
MyClass<T> do_works(Args&&...args)
{
	MyClass<T> r{ std::forward<Args>(args)... };
	//...
	return r;
}
///
int main()
{
	std::string str="qwe";
	auto r = do_works<std::string>("a","b","cc",std::move(str));

}