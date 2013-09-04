#include <thread>
#include <future>
#include <iostream>
#include <chrono>


template< class Function, class... Args>
std::future<typename std::result_of<Function(Args...)>::type> my_async(Function && f, Args && ... args)
{
    typedef typename std::result_of<Function(Args...)>::type ret_type;

	std::promise<ret_type> p;

	auto fut = p.get_future();


	// lambda in separate variable, just to improve readability 
	auto l = [](Function && f, Args && ... args, std::promise<ret_type> && p)
	{
		p.set_value(f(args...));
	};

	std::thread th(l, std::move(f), std::move(args...), std::move(p));

	th.detach();

	return std::move(fut);

}

int wannaRunAsync(int i)
{
	return i;
};

int main()
{

	auto fut = my_async(&wannaRunAsync, 42);

	auto fut2 = my_async([](int i) -> int { return i; }, 42);

	std::cout << fut.get() << std::endl;
	std::cout << fut2.get() << std::endl;

	std::cin.get();

	return 0;
}
