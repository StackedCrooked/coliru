#include <iostream>

template <typename T, T nontype>
struct CL {
    void call() { nontype(123); }
};

void f(int n) {
	std::cout << n << std::endl;
}
CL<void(*)(int), f> cl7;

using df = decltype(f);
CL<df, f> cl8; // << error

int main() {
	cl8.call();
}