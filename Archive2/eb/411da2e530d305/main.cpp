#include <functional>

template <typename T> void f(std::function<void(T)>) {}
template <typename T> void f(std::function<void(T&)>) {}

void f2(std::function<void(int)>) {}
void f2(std::function<void(int&)>) {}

int main()
{
    f<int>([](int) {}); // this compiles
	f2([](int) {}); // this don't
	return 0;
}
