#include <thread>
#include <future>
#include <iostream>
#include <chrono>
#include <type_traits>


template <class _Fret>
struct _P_arg_type
{
    typedef _Fret type;
};

template <class _Fret>
struct _P_arg_type<_Fret&>
{
	typedef _Fret *type;
};

template <>
struct _P_arg_type<void>
{
	typedef int type;
};






template< class Function, class... Args>
std::future<typename std::result_of<Function(Args...)>::type> my_async(Function&& f, Args && ... args)
{
	typedef typename std::result_of<Function(Args...)>::type ret_type;
	//typedef typename _P_arg_type<ret_type>::type _Ptype;

	std::promise<ret_type> p;
	

	auto fut = p.get_future();

	auto l = [](Function && f, Args && ... args, std::promise<ret_type>&& p)
	{
		p.set_value(f(args...));
	};

	std::thread th(l, f, args..., std::move(p));


	th.detach();

	return std::move(fut);

}

int wannaRunAsync(int i)
{
	return i;
};

int main()
{
//	std::function<int(std::promise<int>, int)> f(wannaRunAsync);


	auto fut = my_async(&wannaRunAsync, 42);

	auto fut2 = my_async([](int i) -> int { return i; } , 42);

	std::cout << fut.get() << std::endl;
	std::cout << fut2.get() << std::endl;

	std::cin.get();

	return 0;
}
