#include <iostream>
 
// compile time array to hold result
template<size_t... args>
struct holder {
    static const size_t data[sizeof...(args)];
};
 
template<size_t... args>
const size_t holder<args...>::data[sizeof...(args)] = { args... };
 
template<size_t N, template<size_t> class F, size_t... args>
struct generate {
	typedef typename generate<N-1, F, F<N>::value, args...>::result result;
};
 
template<template<size_t> class F, size_t... args>
struct generate<0, F, args...> {
	typedef holder<F<0>::value, args...> result;
};
 
 
// the say implementation (it must emit `value')
template <size_t E>
struct say {
	enum { value = E * 5 };
};
 
// now a way to go from ints to strings at compile time
#include <boost/mpl/string.hpp>
template <bool B, size_t N>
struct int2str {
	typedef typename boost::mpl::push_back <
		typename int2str<N < 10, N / 10>::type, boost::mpl::char_<'0' + N % 10>>::type type;
};
 
template <>
struct int2str<true, 0> {
	typedef boost::mpl::string<> type;
};
 
template <size_t N>
struct int2str {
	typedef typename boost::mpl::c_str<
		typename int2str<N < 10, N>::type>::type type;
};
 
// and finally a way to concatenate strings at compile time
template <typename S1, typename S2>
struct concat : boost::mpl::insert_range<S1, typename boost::mpl::end<S1>::type, S2> {
	// inherited insert_range
};
 
int main(void) {
	typedef generate<loop, say>::result A; // array of ints
 
	// now build all the strings
	typedef typename int2str<A::data[0]>::type a;
	typedef typename int2str<A::data[1]>::type b;
	typedef typename int2str<A::data[2]>::type c;
	typedef typename int2str<A::data[3]>::type d;
	typedef typename int2str<A::data[4]>::type e;
	typedef typename int2str<A::data[5]>::type f;
	typedef typename int2str<A::data[6]>::type g;
	typedef typename int2str<A::data[7]>::type h;
 
	// now concatenate them all into a string
	typedef concat<a, b>::type aa;
	typedef concat<c, d>::type bb;
	typedef concat<e, f>::type cc;
	typedef concat<g, h>::type dd;
 
	// and those
	typedef concat<aa, bb>::type aaa;
	typedef concat<cc, dd>::type bbb;
 
	// and finally those
	typedef concat<aaa, bbb>::type final;
 
	// and then make it a string
	auto result = boost::mpl::c_str<final>::value;
 
	// now print it
	std::cout << result << std::endl;
}