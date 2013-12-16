#include <string>
#include <typeinfo>
#include <type_traits>
#include <iostream>

template <typename T>
struct TypeString
{
    static std::string value()
	{
		return std::string(typeid(T).name());
	}
};

template <typename T>
struct TypeString<T*>
{
	static std::string value()
	{
		return std::string(typeid(T).name()) + "*";
	}
};

template <typename T>
struct TypeString<const T>
{
	static std::string value()
	{
		return "const " + std::string(typeid(T).name());
	}
};

template <typename T>
struct TypeString<T&>
{
	static std::string value()
	{
		return std::string(typeid(T).name()) + "&";
	}
};

template <typename T>
struct TypeString<const T&>
{
	static std::string value()
	{
		return "const " + std::string(typeid(T).name()) + "&";
	}
};

std::string arguments(void(*func)())
{
	return "";
}

template <typename A>
std::string arguments(void(*func)(A))
{
	return TypeString<A>::value();
}

template <typename A, typename... Args>
std::string arguments(void(*func)(A, Args...))
{
	return TypeString<A>::value() + ", " + arguments((void(*)(Args...))nullptr);
}

template <typename R, typename... Args>
std::string stringify(std::string name, R(*func)(Args...))
{
	return TypeString<R>::value() + " " + name + " (" + arguments((void(*)(Args...))nullptr) + ")";
}

float test(const float&, const bool*, const int, float*, int, size_t) { return 0; }


template <typename R, typename T, typename... Args>
std::string stringify(std::string name, R(T::*)(Args...))
{
	return TypeString<R>::value() + " " + name + " (" + arguments((void(*)(Args...))nullptr) + ")";
}

class Test
{
public:
	void f() { };
};



int main()
{
    auto x = stringify("freetest", test);
	auto y = stringify("membertest", &Test::f);
	std::cout << x << "\n";
    std::cout << y << "\n";
}