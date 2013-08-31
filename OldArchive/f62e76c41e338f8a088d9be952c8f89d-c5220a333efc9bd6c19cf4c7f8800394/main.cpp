// Based on https://github.com/sabel83/mpllibs/blob/master/libs/metaparse/example/compile_to_native_code/main.cpp
// Copyright Abel Sinkovics (abel@sinkovics.hu)  2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <vector>

#include <mpllibs/metaparse/any.hpp>
#include <mpllibs/metaparse/sequence.hpp>
#include <mpllibs/metaparse/lit_c.hpp>
#include <mpllibs/metaparse/last_of.hpp>
#include <mpllibs/metaparse/middle_of.hpp>
#include <mpllibs/metaparse/space.hpp>
#include <mpllibs/metaparse/foldlp.hpp>
#include <mpllibs/metaparse/one_of.hpp>
#include <mpllibs/metaparse/token.hpp>
#include <mpllibs/metaparse/entire_input.hpp>
#include <mpllibs/metaparse/string.hpp>
#include <mpllibs/metaparse/transform.hpp>
#include <mpllibs/metaparse/always.hpp>
#include <mpllibs/metaparse/build_parser.hpp>
#include <mpllibs/metaparse/keyword.hpp>

#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/back.hpp>
#include <boost/mpl/bool.hpp>

#include <boost/proto/proto.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/make_vector.hpp>

using mpllibs::metaparse::sequence;
using mpllibs::metaparse::lit_c;
using mpllibs::metaparse::last_of;
using mpllibs::metaparse::middle_of;
using mpllibs::metaparse::space;
using mpllibs::metaparse::any;
using mpllibs::metaparse::build_parser;
using mpllibs::metaparse::foldlp;
using mpllibs::metaparse::one_of;
using mpllibs::metaparse::token;
using mpllibs::metaparse::entire_input;
using mpllibs::metaparse::transform;
using mpllibs::metaparse::always;
using mpllibs::metaparse::keyword;

using boost::mpl::apply_wrap1;
using boost::mpl::front;
using boost::mpl::back;
using boost::mpl::bool_;


struct build_or
{
    typedef build_or type;

	template <class C, class State>
	struct apply
	{
		typedef apply type;
		typedef typename boost::proto::logical_or<typename State::proto_type, typename back<C>::type::proto_type >::type proto_type;
	};
};

struct build_and
{
	typedef build_and type;

	template <class C, class State>
	struct apply
	{
		typedef apply type;
		typedef typename boost::proto::logical_and<typename State::proto_type, typename back<C>::type::proto_type >::type proto_type;
	};
};



template<bool I>
struct value
{};

struct build_value
{
	typedef build_value type;

	template <class V>
	struct apply
	{
		typedef apply type;
		typedef typename boost::proto::terminal<value<V::type::value> >::type proto_type;
	};
};

struct build_not
{
	typedef build_not type;

	template <class V>
	struct apply
	{
		typedef apply type;
		typedef typename boost::proto::logical_not<typename V::proto_type >::type proto_type;
	};
};

template<int I>
struct placeholder
{};

template<int I>
struct arg
{
	typedef arg type;
	typedef typename boost::proto::terminal<placeholder<I> >::type proto_type;
};

#ifdef _S
#error _S already defined
#endif
#define _S MPLLIBS_STRING

typedef token < keyword < _S ( "&&" ) > > and_token;
typedef token < keyword < _S ( "||" ) > > or_token;
typedef token < lit_c < '!' > > not_token;

typedef token < keyword < _S ( "true" ), bool_<true> > > true_token;
typedef token < keyword < _S ( "false" ), bool_<false> > > false_token;

typedef token < lit_c < 'a' > > arg1_token;
typedef token < lit_c < 'b' > > arg2_token;
typedef token < lit_c < 'c' > > arg3_token;


struct paren_exp;

typedef
one_of< paren_exp, transform<true_token, build_value>, transform<false_token, build_value>, always<arg1_token, arg<0> >, always<arg2_token, arg<1> >, always<arg3_token, arg<2> > >
value_exp; //value_exp = paren_exp | true_token | false_token | arg1_token | arg2_token | arg3_token;

typedef
one_of< transform<last_of<not_token, value_exp>, build_not>, value_exp>
not_exp; //not_exp = (omit[not_token] >> value_exp) | value_exp;

typedef
foldlp <
sequence<and_token, not_exp>,
         not_exp,
         build_and
         >
         and_exp; // and_exp = not_exp >> *(and_token >> not_exp);

typedef
foldlp <
sequence<or_token, and_exp>,
         and_exp,
         build_or
         >
         or_exp; // or_exp = and_exp >> *(or_token >> and_exp);

struct paren_exp: middle_of < lit_c < '(' > , or_exp, lit_c < ')' > > {}; //paren_exp = lit('(') >> or_exp >> lit('(');

typedef last_of<any<space>, or_exp> expression; //expression = omit[*space] >> or_exp;

typedef build_parser<entire_input<expression> > function_parser;


template <typename Args>
struct calculator_context
		: boost::proto::callable_context< calculator_context<Args> const >
{
	calculator_context ( const Args& args ) : args_ ( args ) {}
	// Values to replace the placeholders
	const Args& args_;

	// Define the result type of the calculator.
	// (This makes the calculator_context "callable".)
	typedef bool result_type;

	// Handle the placeholders:
	template<int I>
	bool operator() ( boost::proto::tag::terminal, placeholder<I> ) const
	{
		return boost::fusion::at_c<I> ( args_ );
	}

	template<bool I>
	bool operator() ( boost::proto::tag::terminal, value<I> ) const
	{
		return I;
	}
};

template <typename Args>
calculator_context<Args> make_context ( const Args& args )
{
	return calculator_context<Args> ( args );
}

template <typename Expr, typename ... Args>
int evaluate ( const Expr& expr, const Args& ... args )
{
	return boost::proto::eval ( expr, make_context ( boost::fusion::make_vector ( args... ) ) );
}

#ifdef LAMBDA
#error LAMBDA already defined
#endif
#define LAMBDA(exp) apply_wrap1<function_parser, MPLLIBS_STRING(exp)>::type::proto_type()

int main()
{
	using std::cout;
	using std::endl;

	cout << evaluate ( LAMBDA ( "true&&false" ) ) << endl;
	cout << evaluate ( LAMBDA ( "true&&a" ), false ) << endl;
	cout << evaluate ( LAMBDA ( "true&&a" ), true ) << endl;
	cout << evaluate ( LAMBDA ( "a&&b" ), true, false ) << endl;
	cout << evaluate ( LAMBDA ( "a&&(b||c)" ), true, false, true ) << endl;
	cout << evaluate ( LAMBDA ( "!a&&(false||(b&&!c||false))" ), false, true, false ) << endl;
}
