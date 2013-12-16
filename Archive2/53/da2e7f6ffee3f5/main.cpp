#include <string>
#include <typeinfo>
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

template <typename... Args>
struct unpack
{
	using type = void(*)(Args...);
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

template <typename R, typename... A>
std::string stringify(std::string name, R(*func)(A...))
{
	return TypeString<R>::value() + " " + name + " (" + arguments((void(*)(A...))nullptr) + ")";
}

float test(const float&, const bool*, const int, float*, int, size_t) { return 0; }

int main()
{
	std::cout << stringify("testme", test);
}