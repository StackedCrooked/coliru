#include <iostream>
#include <string>
#include <functional>

int foo(int, int) { return 0; }
int bar(int, int, int, int) { return 0; }

template <typename T, typename... Params>
void benchmark(int t, std::function<T(Params...)> f, Params&&... params)
{
    //std::cout << "Evaluating " << name << " " << t << " times ...";

	for(int i = 0; i < t; ++i)
		f(std::forward<Params>(params)...); // Problem!

	std::cout << " done!\n";
}

int main()
{
    std::function<int(int, int)> f = &foo;
	benchmark<int>(10, f, 1, 2);

	//Won't compile!
    std::function<int(int, int, int, int)> b = &bar;
	benchmark<int>(10, b, 1, 2, 3, 4);
}