#include <iostream>
#include <string>
#include <vector>

template<typename F> 
struct arity;

template<typename R, typename ...Args> 
struct arity<R (*)(Args...)>
{
    static const std::size_t value = sizeof ... (Args);
};

template<int ... N>
struct seq
{
	using type = seq<N...>;

	template<int I>
	struct push_back : seq<N..., I> {};
};

template<int N>
struct genseq : genseq<N-1>::type::template push_back<N-1> {};

template<>
struct genseq<0> : seq<> {};

template<int N>
using genseq_t = typename genseq<N>::type;
        
template<typename F, typename ArgEvaluator, int ...N>
void invoke(seq<N...>, F f, ArgEvaluator arg_evaluator)
{
    f((N, arg_evaluator())...);
}


int foo(int i, int j) {  std::cout << "foo(" << i << "," << j << ")\n"; return 0; }
int bar(int i, int j, int k) {  std::cout << "bar(" << i << "," << j << "," << k << ")\n"; return 0; }


template<typename F>
void test_func(F f)
{
    int i=0;
    auto arg_evaluator = [i]() mutable { return ++i; };
    invoke(genseq_t<arity<F>::value>(), f, arg_evaluator);
}

int main()
{
    test_func(foo);
    test_func(bar);
}