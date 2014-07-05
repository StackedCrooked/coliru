#include <iostream>
#include <chrono>

template<int N>
struct Fib
{
    static constexpr int value = Fib<N - 1>::value + Fib<N - 2>::value;
};

template<>
struct Fib<1>
{
	static constexpr int value = 1;
};

template<>
struct Fib<0>
{
	static constexpr int value = 0;
};

int fib(int x)
{
	if(x < 3)
		return 1;

	return fib(x - 2) + fib(x - 1);
}


int main()
{
	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();
	std::cout << Fib<42>::value;
	end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	std::cout << " Functional: " << elapsed_seconds.count() << "s.";

	std::cout << std::endl;

	std::chrono::time_point<std::chrono::system_clock> start1, end1;
	start1 = std::chrono::system_clock::now();
	std::cout << fib(42);
	end1 = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds1 = end1 - start1;
	std::cout << " Standard recursion: " << elapsed_seconds1.count() << "s.";
	return 0;
}
