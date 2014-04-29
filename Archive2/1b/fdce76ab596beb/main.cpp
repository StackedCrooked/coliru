#include "variant.hpp"
#include <boost/variant.hpp>
#include <boost/variant/multivisitors.hpp>

#include <iostream>

using namespace insituc;

struct P
	: boost::static_visitor< void >
{

	template< typename ...T >
	auto
	operator () (T &&...) const
	{
		//return __PRETTY_FUNCTION__;
	}

};

int main()
{
	struct A {};
	struct B {};
	struct C {};
	struct D {};
	struct E {};
	using V = boost::variant< A, B, C, D, E >;
	P p;
	V v0(A{}), v1(B{}), v2(C{}), v3(D{}), v4(E{});
	boost::apply_visitor(p, v0, v1, v2, v3, v4);
}

