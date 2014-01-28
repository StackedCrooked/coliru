#include <iostream>

#ifndef WIN32
#define __stdcall
#endif

template<typename... Args>
struct get_proc_address_wrapper;

template<typename... Args>
struct get_proc_address_wrapper<unsigned(Args...)>
{
    typedef unsigned(__stdcall *func_type)(Args...);
	get_proc_address_wrapper(func_type pf)
		: pf(pf)
	{}

	unsigned operator()(Args... args)
	{
		if (not pf) return static_cast<unsigned>(-1);
		else return (*pf)(args...);
	}

	func_type pf;
};

unsigned __stdcall foo1()
{
	return 1;
}

unsigned __stdcall foo2(int)
{
	return 2;
}

unsigned __stdcall foo3(int, int)
{
	return 3;
}

int main()
{
	{
		get_proc_address_wrapper<unsigned()> p1(&foo1);
		get_proc_address_wrapper<unsigned()> p2(nullptr);
		std::cout << "good: " << p1() << '\n';
		std::cout << "bad: " << p2() << '\n';
	}
	{
		get_proc_address_wrapper<unsigned(int)> p1(&foo2);
		get_proc_address_wrapper<unsigned(int)> p2(nullptr);
		std::cout << "good: " << p1(10) << '\n';
		std::cout << "bad: " << p2(10) << '\n';
	}
	{
		get_proc_address_wrapper<unsigned(int, int)> p1(&foo3);
		get_proc_address_wrapper<unsigned(int, int)> p2(nullptr);
		std::cout << "good: " << p1(10, 20) << '\n';
		std::cout << "bad: " << p2(10, 20) << '\n';
	}
}
