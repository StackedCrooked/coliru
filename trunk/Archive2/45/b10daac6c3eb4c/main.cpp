#include <functional>

template<typename T>
void f()
{
    typename std::function<T>::result_type returnVal;
	static_assert(std::is_same<decltype(returnVal), int>::value, "");
	(void)returnVal;

	typename std::function<T>::first_argument_type arg1Val;
	static_assert(std::is_same<decltype(arg1Val), double>::value, "");
	(void)arg1Val;

	typename std::function<T>::second_argument_type arg2Val;
	static_assert(std::is_same<decltype(arg2Val), char>::value, "");
	(void)arg2Val;
}

int main()
{
	f<int(double, char)>();
}