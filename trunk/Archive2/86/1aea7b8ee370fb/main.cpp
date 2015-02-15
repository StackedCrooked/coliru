#include <iostream>
#include <string>
#include <functional>
#include <type_traits>

class value;
using std::string;
typedef std::function<value(unsigned int argc, const value* argv)> function;

template<typename T> struct value_kind;
template<> struct  value_kind<int> : std::integral_constant<int, 0> {};
template<> struct  value_kind<double> : std::integral_constant<int, 1>{};
template<> struct  value_kind<string> : std::integral_constant<int, 2>{};
template<> struct  value_kind<function> : std::integral_constant<int, 3>{};

class value
{
public:
    value(int i) { kind_ = 0; new(&data_)int(i); }
	value(double f) { kind_ = 1; new(&data_)double(f); }
	value(string s) { kind_ = 2; new(&data_)string(s); }
	value(function func) { kind_ = 3; new(&data_)function(func); }

	template<typename T>
	T const& get() const
	{
		if (value_kind<T>::value != kind_) throw std::bad_cast();
		return *reinterpret_cast<T const*>(&data_);
	}
private:
	std::aligned_storage<1024>::type data_;
	int kind_;
};

template<typename R, typename P0>
value vfunc(std::function<R(P0)> func)
{
	return value([func](unsigned int argc, const value* argv) -> value
	{
		R r = func(argc >= 1 ? argv[0].get<P0>() : P0());
		return value(r);
	});
}
template<typename R, typename P0, typename P1>
value vfunc(std::function<R(P0, P1)> func)
{
	return value([func](unsigned int argc, const value* argv) -> value
	{
		R r = func(argc >= 1 ? argv[0].get<P0>() : P0(),
			argc >= 2 ? argv[1].get<P1>() : P1());
		return value(r);
	});
}

/////////////////////////////////////////////////////////////////////////////
template<typename Function>
struct function_traits : public function_traits<decltype(&Function::operator())>
{
};

// []() -> R
template<typename Lambda, typename R>
struct function_traits<R(Lambda::*)() const>
{
	typedef std::function<R()> function;
};

// []() mutable -> R
template<typename Lambda, typename R>
struct function_traits<R(Lambda::*)()>
{
	typedef std::function<R()> function;
};

// [](P0) -> R
template<typename Lambda, typename R, typename P0>
struct function_traits<R(Lambda::*)(P0) const>
{
	typedef std::function<R(P0)> function;
};

// [](P0) mutable -> R
template<typename Lambda, typename R, typename P0>
struct function_traits<R(Lambda::*)(P0)>
{
	typedef std::function<R(P0)> function;
};

// [](P0, P1) -> R
template<typename Lambda, typename R, typename P0, typename P1>
struct function_traits<R(Lambda::*)(P0, P1) const>
{
	typedef std::function<R(P0, P1)> function;
};

// [](P0, P1) mutable -> R
template<typename Lambda, typename R, typename P0, typename P1>
struct function_traits<R(Lambda::*)(P0, P1)>
{
	typedef std::function<R(P0, P1)> function;
};

template <typename Function>
struct function_traits<Function&> :function_traits<Function>{};

template <typename Function>
struct function_traits<Function&&> :function_traits<Function>{};

template<typename Lambda> //TODO: enable_if Lambda::operator() ?
value vfunc(Lambda&& lambda)
{
	typedef typename function_traits<Lambda>::function function;
	return vfunc(static_cast<function>(lambda));
}
/////////////////////////////////////////////////////////////////////////////

int main()
try
{
	value local_func = vfunc( [](int a, int b) { return a + b; } );

	std::function<int(int,int)> t = [](int a, int b) { return a + b; };
	value local_func2 = vfunc( t );

	value args[] = { 1, 2 };
	value r = local_func.get<function>()(2, args);
	std::cout << r.get<int>() << '\n';

	value r2 = local_func2.get<function>()(2, args);
	std::cout << r2.get<int>() << '\n';
}
catch (std::exception const& ex)
{
	std::cerr << ex.what() << '\n';
}
