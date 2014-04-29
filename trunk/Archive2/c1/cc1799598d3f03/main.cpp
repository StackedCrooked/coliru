#include "variant_fwd.hpp"
#include "recursive_wrapper.hpp"
#include "traits.hpp"
#include "variant.hpp"
#include "visitor.hpp"

#include <boost/variant.hpp>
#include <boost/variant/multivisitors.hpp>

#include <iostream>

struct P
	: boost::static_visitor< char const * >
{

	template< typename ...T >
	auto
	operator () (T &&...) const
	{
		return __PRETTY_FUNCTION__;
	}

};

int main()
{
    using insituc::variant;
    using insituc::apply_visitor;
	struct A {};
	struct B {};
	struct C {};
	struct D {};
	using V = /*boost::*/variant< A, B, C, D >;
	P p;
	V v0(A{}), v1(B{}), v2(C{}), v3(D{});
	std::cout << /*boost::*/apply_visitor(p, v0, v1, v2, v3) << std::endl;
}

