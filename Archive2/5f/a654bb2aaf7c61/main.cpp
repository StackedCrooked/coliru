#include <iostream>
#include <string>
#include <functional>
#include <random>
#include <ctime>

int foo(int, int) { return 0; }
int bar(int, int, int, int) { return 0; }

template <typename T, typename F>
void benchmark(int t, F f, const std::string& name)
{
    std::mt19937 rng(std::time(0));
	std::uniform_int_distribution<T> uint_dist10(0, std::numeric_limits<T>::max());

	std::cout << "Evaluating " << name << " " << t << " times ...";

	for(int i = 0; i < t; ++i)
		f(rng(), rng()); // Problem?

	std::cout << " done!\n";
}

int main()
{
	// Ideal usage:
	// benchmark(10, foo, "foo");

	benchmark<int>(10, foo, "foo");

	// Won't compile!
	//benchmark<int, int, int, int>(10, bar, "bar");
}