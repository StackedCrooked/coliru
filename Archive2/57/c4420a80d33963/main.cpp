#include <iostream>

struct Y
{
    Y() { std::cout << "default ctor\n"; }

	Y(const Y&) { std::cout << "copy ctor\n"; }
	template<typename T>
	Y(T const&) { std::cout << "copy<T> ctor\n"; }

	Y(Y&&) { std::cout << "move ctor\n"; }
    template<typename T,
		typename = typename std::enable_if<!std::is_same<Y,
			typename std::decay<T>::type>::value>::type>
	Y(T&& y) { std::cout << "move<T> ctor\n"; }
};

template<typename ...Args>
void unused(Args&&...) {}

int main()
{
    Y y1;
    Y y2 = y1;
    Y y3 = std::move(y1);
    Y y4 = true;
    
    unused(y1, y2, y3, y4);
}
