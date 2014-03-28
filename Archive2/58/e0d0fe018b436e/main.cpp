#include <iostream>

template<typename T>
struct Wrapper
{
    T &t;
	Wrapper(T &t)
	: t(t)
	{
	}
	void rebind(T &t)
	{
		this->~Wrapper();
		new (this) Wrapper(t);
	}
};

int main()
{
	int x = 7, y = 4;
	Wrapper<int> w = x;
	std::cout << x << " " << y << std::endl;
	w.t = 2;
	std::cout << x << " " << y << std::endl;
	w.rebind(y);
	std::cout << x << " " << y << std::endl;
	w.t = 14;
	std::cout << x << " " << y << std::endl;
}
