#include <tuple>
#include <iostream>

// sequence

template<size_t...>
struct Sequence
{ };

template<size_t N, size_t... Seq>
struct GenerateSequence : GenerateSequence<N - 1, N - 1, Seq...>
{ };

template<size_t... Seq>
struct GenerateSequence<0, Seq...>
{
    using type = Sequence<Seq...>;
};

// invoke tuple

struct TupleForEachInvoker
{
	template<typename Func, typename ForEachFunc, typename Tuple, size_t... Seq>
	static auto invoke(Func&& func, ForEachFunc&& forEachFunc, Tuple&& tuple, Sequence<Seq...>)
		-> decltype(func(forEachFunc(std::get<Seq>(std::forward<Tuple>(tuple)))...))
	{
		return func(forEachFunc(std::get<Seq>(std::forward<Tuple>(tuple)))...);
	}

	template<typename Func, typename ForEachFunc, typename Tuple>
	static auto apply(Func&& func, ForEachFunc&& forEachFunc, Tuple&& args)
		-> decltype(invoke(std::forward<Func>(func),
						   std::forward<ForEachFunc>(forEachFunc),
						   std::forward<Tuple>(args),
						   typename GenerateSequence<std::tuple_size<std::decay_t<Tuple>>::value>::type()))
	{
		return invoke(std::forward<Func>(func),
					  std::forward<ForEachFunc>(forEachFunc),
					  std::forward<Tuple>(args),
					  typename GenerateSequence<std::tuple_size<std::decay_t<Tuple>>::value>::type());
	}
};

template<typename Func, typename ForEachFunc, typename Tuple>
inline auto invokeWithMemberFromAll(Func&& func, ForEachFunc&& forEachFunc, Tuple&& tuple)
    -> decltype(TupleForEachInvoker::apply(std::forward<Func>(func),
    									   std::forward<ForEachFunc>(forEachFunc),
    									   std::forward<Tuple>(tuple)))
{
    return TupleForEachInvoker::apply(std::forward<Func>(func),
    								  std::forward<ForEachFunc>(forEachFunc),
    								  std::forward<Tuple>(tuple));
}

// exemplar

template<typename T>
struct Foo
{
    T& data() { return _val; }
	T _val;
};

struct Extract
{
    template<typename T>
    T& operator() (Foo<T>& f) { return f.data(); }
};

int main()
{
	Foo<int>         i { 5 };
	Foo<double>      d { 6. };
	Foo<const char*> s { "hello world" };

	auto cb = [](int& i, const double& d, const char* s)
		{
			std::cout << "i=" << i << ", d=" << d << ", s=" << s << std::endl;
			
			i += 2;
		};


	// rvalue reference to tuple
	invokeWithMemberFromAll(cb, Extract{}, std::tie(i, d, s));

    std::cout << i.data() << std::endl;

	// lvalue reference to tuple - fails
	auto tuple = std::tie(i, d, s);
	invokeWithMemberFromAll(cb, Extract{}, tuple);
	
    std::cout << i.data() << std::endl;

}
