#include <iostream>
using namespace std;

template<typename> struct argument;

template<typename T>
struct argument<void (T)>
{
    using type = T;
};

template<typename T, void(*f)(T t)>
struct deleter_impl
{
    using pointer = T;
	void operator()(T t) {
		f(t);
	}
};

#define deleter(X) deleter_impl<typename argument<decltype(X)>::type, X>

int main() {
	deleter(free) q;
    q(nullptr);
}