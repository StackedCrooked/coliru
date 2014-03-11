
#include <iostream>
#include <tuple>
//#include "../utils/generate_indices.h"


// === BEGIN utils copy/paste ================================================

namespace utils {

template<typename T>
using Invoke = typename T::type;


template<int... Is>
struct int_list
{
    template<int I>
	using push_front = int_list<I, Is...>;

	template<int I>
	using push_back = int_list<Is..., I>;
};


namespace detail {

template<typename L, typename R>
struct append_impl;

template<int... Ls, int... Rs>
struct append_impl<int_list<Ls...>, int_list<Rs...>>
{
	using type = int_list<Ls..., Rs...>;
};

} // namespace detail

template<typename L, typename R>
using append = Invoke<detail::append_impl<L, R>>;


template<int... Is>
using indices = int_list<Is...>;


struct increasing_tag { };
struct decreasing_tag { };

namespace detail {

// inc
template<int N, int S>
struct generate_inc_indices
{
	using type = append<Invoke<generate_inc_indices<N/2, S>>, Invoke<generate_inc_indices<N - N/2, S + N/2>>>;
};

template<int S>
struct generate_inc_indices<1, S>
{
	using type = indices<S>;
};

template<int S>
struct generate_inc_indices<0, S>
{
	using type = indices<>;
};

// dec
template<int N, int S>
struct generate_dec_indices
{
	using type = append<Invoke<generate_dec_indices<N - N/2, S + N/2>>, Invoke<generate_dec_indices<N/2, S>>>;
};

template<int S>
struct generate_dec_indices<1, S>
{
	using type = indices<S>;
};

template<int S>
struct generate_dec_indices<0, S>
{
	using type = indices<>;
};


// impl inc/dec
template<int N, typename Tag, int Shift>
struct generate_indices_impl;

template<int N, int Shift>
struct generate_indices_impl<N, increasing_tag, Shift>
{
	using type = typename generate_inc_indices<N, Shift>::type;
};

template<int N, int Shift>
struct generate_indices_impl<N, decreasing_tag, Shift>
{
	using type = typename generate_dec_indices<N, Shift>::type;
};

} // namespace detail {


template<int N, typename Tag = increasing_tag, int Shift = 0>
using generate_indices = typename detail::generate_indices_impl<N, Tag, Shift>::type;


} // namespace utils {

// === END utils copy/paste ==================================================


namespace detail {

template<typename Func>
class TupleCall
{
public:
	explicit TupleCall(Func f) : func(std::move(f))
	{ }

	template<typename... Ts>
	void operator()(const std::tuple<Ts...>& tup) const
	{
		call(tup);
	}

private:

	template<typename... Ts, int... Is>
	void expand_call(const std::tuple<Ts...>& tup, utils::indices<Is...>) const
	{
		auto unpack = {0, (call(std::get<Is>(tup)), 0)...};
		(void)unpack;
	}

	template<typename T>
	void call(const T& t) const
	{
		func(t);
	}

	template<typename... Ts>
	void call(const std::tuple<Ts...>& tup) const
	{
		expand_call(tup, utils::generate_indices<sizeof...(Ts)>());
	}

	Func func;
};

} // namespace detail {

template<typename Func, typename... Ts>
void tuple_call(const std::tuple<Ts...>& tup, Func&& func)
{
	detail::TupleCall<Func>(std::forward<Func>(func))(tup);
}

// ---------------------------------------------------------------------------


template<typename... Ts>
class Test
{
public:
	template<typename Func>
	void call(Func&& f) const
	{
		tuple_call(tup, std::forward<Func>(f));
	}
    
    void name2() const
    {
        // C++14
        tuple_call(tup, [](const auto& p) { std::cout << "2 - " << p.name() << "\n"; });
    }

private:
	std::tuple<Ts...> tup;
};


// ---------------------------------------------------------------------------


struct one
{
	//static constexpr const char* name = "one";
    static constexpr const char* name() { return "one"; }
};

//constexpr const char* one::name;

struct two 
{
	//static constexpr const char* name = "two";
    static constexpr const char* name() { return "two"; }
};

//constexpr const char* two::name;


struct printer
{
	template<typename T>
	void operator()(const T& t) const
	{
		std::cout << t.name() << "\n";
	}
};

int main()
{
	Test<one, two, one> t1;
	t1.call(printer());
    t1.name2();

	std::cout << "---\n";

	Test<
		one,
		std::tuple<one, two>,
		two,
		std::tuple<
			one,
			std::tuple<two, two>
		>,
		one
	> t2;
	t2.call(printer());
    //t2.name2();

	return 0;
}

