#include <iostream>
#include <tuple>

template<unsigned...Is> struct indexes {typedef indexes<Is...> type;};
template<unsigned min, unsigned max, unsigned...Is> struct make_indexes: make_indexes<min, max-1, max-1, Is...> {};
template<unsigned min, unsigned...Is> struct make_indexes<min, min, Is...>: indexes<Is...> {};

template<unsigned max, unsigned min=0>
using Indexes = typename make_indexes<min, max>::type;

template<unsigned index, typename Functor, typename... Args, unsigned... Before, unsigned... After>
void map_bool_to_compile_time_helper( indexes<Before...>, indexes<After...>, Functor&& f, std::tuple<Args...> args )
{
	if (std::get<index>( args )) {
		std::forward<Functor>(f)( std::get<Before>(args)..., std::true_type(), std::get<After>(args)... );
	} else {
		std::forward<Functor>(f)( std::get<Before>(args)..., std::false_type(), std::get<After>(args)... );
	}
}

template<unsigned index, typename Functor, typename... Args>
void map_bool_to_compile_time( Functor&& f, Args&&... args )
{
	map_bool_to_compile_time_helper<index>( Indexes<index>(), Indexes<sizeof...(Args), index+1>(), std::forward<Functor>(f), std::make_tuple<Args&&...>(std::forward<Args>(args)...) );
}

template<typename Functor, unsigned... indexes>
struct map_bools_to_compile_time_helper;

template<typename Functor, unsigned index, unsigned... indexes>
struct map_bools_to_compile_time_helper<Functor, index, indexes...> {
    Functor&& f;
    map_bools_to_compile_time_helper(Functor&& in):f(std::forward<Functor>(in)) {}
    template< typename... Args>
    void operator()( Args&&... args) const {
        map_bool_to_compile_time<index>( map_bools_to_compile_time_helper<Functor, indexes...>{std::forward<Functor>(f)}, std::forward<Args>(args)... );
    }
};
template<typename Functor>
struct map_bools_to_compile_time_helper<Functor> {
    Functor&& f;
    map_bools_to_compile_time_helper(Functor&& in):f(std::forward<Functor>(in)) {}
    template<typename... Args>
    void operator()( Args&&... args) const {
        std::forward<Functor>(f)(std::forward<Args>(args)...);
    }
};

template<unsigned... Is, typename Functor, typename... Args>
void map_bools_to_compile_time( indexes<Is...>, Functor&& f, Args&&... args ) {
    map_bools_to_compile_time_helper<Functor, Is...>{ std::forward<Functor>(f) }( std::forward<Args>(args)... );
}

struct make_compile_time_bool_t {
    bool t;
    static constexpr bool min = false;
    static constexpr bool max = true;
    operator bool() const { return t; }
};

template<typename T, T Max, T Min>
struct make_compile_time_t {
    T t;
    static constexpr bool min = Min;
    static constexpr bool max = Max;
    operator T() const { return t; }
};

make_compile_time_bool_t compile_time( bool b ) { return {b}; }

template<typename I0, typename I1>
struct concat;
template<unsigned... I0, unsigned... I1>
struct concat< indexes<I0...>, indexes<I1...> >:indexes<I0..., I1...> {};

template<template<class>class test, unsigned offset, typename Arg, typename=void>
struct index_if_passes_test:indexes<> {};
template<template<class>class test, unsigned offset, typename Arg>
struct index_if_passes_test<test, offset, Arg, typename std::enable_if<test<Arg>::value>::type>:indexes<offset> {};
template<template<class>class test, unsigned offset, typename Arg>
using check_test = typename index_if_passes_test<test,offset,Arg>::type;
template<template<class>class test, unsigned offset, typename... Args>
struct indexes_that_pass_test;
template<template<class>class test, unsigned offset, typename A0, typename... Args>
struct indexes_that_pass_test<test, offset, A0, Args...>:
    concat< check_test<test,offset,A0>, typename indexes_that_pass_test<test, offset+1, Args... >::type >
{};
template<template<class>class test, unsigned offset>
struct indexes_that_pass_test<test, offset>:indexes<> {};

template<typename T>
struct is_compile_time_argument:std::false_type {};
template<>
struct is_compile_time_argument<make_compile_time_bool_t>:std::true_type {};
template<typename T, T Min, T Max>
struct is_compile_time_argument<make_compile_time_t<T, Min, Max>>:std::true_type {};

template<typename... Args>
using compile_time_indexes = typename indexes_that_pass_test< is_compile_time_argument, 0, Args...>::type;

template<typename Functor, typename... Args>
void compile_time_eval( Functor&& f, Args&&... args ) {
    map_bools_to_compile_time( compile_time_indexes<typename std::decay<Args>::type...>(), std::forward<Functor>(f), std::forward<Args>(args)... );
}

struct test {
    template<bool b>
    void operator()( int x, std::integral_constant< bool, b > )  { std::cout << x << ": " << b <<"!\n"; } 
};

struct test2 {
    template<bool b0, bool b1, bool b2>
    void operator()( int x, std::integral_constant< bool, b0 >, std::integral_constant< bool, b1 >, std::integral_constant< bool, b2 > )
    {
        std::cout << x << ": " << b0 << b1 << b2 << "\n";
    }
};
int main(int argc, char** argv) {
    bool b = argc > 1;
    compile_time_eval( test(), 1, compile_time(b) );
    compile_time_eval( test(), 2, compile_time(!b) );
    compile_time_eval( test2(), 3, compile_time(true), compile_time(false!=b), compile_time(true) );
}
