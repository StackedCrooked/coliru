#include <functional>
#include <iostream>
#include <string>

template<class TFunc>
class hook_function : public std::function<TFunc>
{
public:
    typedef std::function<TFunc> FuncType;
	FuncType original;

	void hook()
	{
		std::cout << "Called." << std::endl;
	}

	hook_function() : FuncType()
	{}

	template<typename T>
	hook_function(T&& fn) 
		: original(std::forward<T>(fn)) 
		, FuncType(std::forward<T>(fn))
	{
	}

	hook_function(hook_function&& other) 
		: FuncType(static_cast<FuncType&&>(other))
	{
	}

	hook_function& operator=(hook_function&& other)
	{
		FuncType::operator=(static_cast<FuncType&&>(other));
		return *this;
	}

	void operator()(int a, int b)
	{
		hook();
		original(a, b);
	}

	void operator()(const std::string s)
	{
		hook();
		original(s);
	}
};

class Callback
{
public:
	Callback(hook_function<void(const std::string&)> cb) 
	{ 
		cb("Callback constructor."); 
	}
};

int main()
{
	hook_function<void(int, int)> cb = [](int a, int b)
	{ 
		std::cout << a << " " << b << std::endl; 
	};

	cb(100, 200);

	Callback theCallback([](const std::string str) 
	{
		std::cout << "theCallback: " << str << std::endl;
	});

}