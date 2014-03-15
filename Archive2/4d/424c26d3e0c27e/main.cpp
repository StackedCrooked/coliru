
#ifndef ADAPT_PHOENIX_PLACEHOLDER_HPP
#define ADAPT_PHOENIX_PLACEHOLDER_HPP

#include <boost/phoenix/core.hpp>
#include <boost/phoenix/bind.hpp>

namespace adapt_phoenix
{

    template <typename Type, typename Expr>
	struct placeholder;


	template <typename Type>
	struct is_adapted : boost::mpl::false_
	{};

	template <typename Type>
	struct is_adapted<Type*> :is_adapted<Type>
	{};

	template <typename Type>
	struct is_adapted<Type()> :is_adapted<Type>
	{};
    
#define GENERATE_IS_ADAPTED_FOR_FUNCTIONS(_,N,__) \
	template <typename Type, BOOST_PHOENIX_typename_A(N)> \
	struct is_adapted<Type(BOOST_PHOENIX_A(N))> : is_adapted<Type> \
	{};

	BOOST_PP_REPEAT_FROM_TO(1, BOOST_PHOENIX_COMPOSITE_LIMIT, GENERATE_IS_ADAPTED_FOR_FUNCTIONS, _)
#undef GENERATE_IS_ADAPTED_FOR_FUNCTIONS


	namespace detail
	{
		template <typename Pointee, typename Expr>
		struct pointer : Pointee
		{
			pointer(const Expr& expr_) :Pointee(expr_){}

			const Pointee& operator*() const
			{
				return *this;
			}

			const Pointee* operator->() const
			{
				return this;
			}
		};
	}

	template <typename Type, typename Expr>
	struct placeholder<Type*, Expr>: detail::pointer<placeholder<Type, Expr>, Expr >
	{
		placeholder(const Expr& expr) : detail::pointer<placeholder<Type, Expr>, Expr>(expr){}
	};
    
    #define GENERATE_ARG_PLACEHOLDER(_,N,__) \
    template <typename Adapted> \
    struct BOOST_PP_CAT(arg,N) : placeholder<Adapted,boost::phoenix::expression::argument<N>::type> \
    { \
        BOOST_PP_CAT(arg,N)() : placeholder<Adapted,boost::phoenix::expression::argument<N>::type>(){} \
    };
    
    BOOST_PP_REPEAT_FROM_TO(1, BOOST_PHOENIX_ARG_LIMIT, GENERATE_ARG_PLACEHOLDER, _)
    #undef GENERATE_ARG_PLACEHOLDER


	namespace detail
	{
		template <typename Adapted, typename Expr>
		struct do_nothing : Expr
		{
			do_nothing(const Expr& expr) :Expr(expr){}
		};

		template <typename R, typename Member, typename Expr>
		struct member_variable : boost::phoenix::detail::expression::function_eval<
			boost::phoenix::detail::member_variable<R, Member>,
			Expr
		>::type
		{
			typedef boost::phoenix::detail::member_variable<R, Member> member_variable_type;

			typedef boost::phoenix::detail::expression::function_eval<
				member_variable_type,
				Expr
			> function_eval_type;

			typedef typename function_eval_type::type base_type;

			member_variable(Member member, const Expr& expr) : base_type(function_eval_type::make(member_variable_type(member), expr)) {}
			member_variable(const member_variable& other) : base_type(other) {}
		};

		template <typename R, typename Member, typename Expr>
		struct member_function;

		template <typename R, typename Member, typename Expr>
		struct member_function<R(), Member, Expr> : boost::phoenix::detail::expression::function_eval<
			boost::phoenix::detail::member_function_ptr<0, R, Member>,
			Expr
		>::type
		{
			typedef boost::phoenix::detail::member_function_ptr<0, R, Member> member_function_type;

			typedef boost::phoenix::detail::expression::function_eval<
				member_function_type,
				Expr
			> function_eval_type;

			typedef typename function_eval_type::type base_type;

			member_function(Member member, const Expr& expr) : base_type(function_eval_type::make(member_function_type(member), expr)) {}
			member_function(const member_function& other) : base_type(other) {}

		};

#define GENERATE_MEMBER_FUNCTION(_,N,__) \
	template <typename R, typename Member, typename Expr, BOOST_PHOENIX_typename_A(N)> \
		struct member_function<R(BOOST_PHOENIX_A(N)), Member, Expr> : boost::phoenix::detail::expression::function_eval< \
		boost::phoenix::detail::member_function_ptr<N, R, Member>, \
		Expr, BOOST_PHOENIX_A(N) \
		>::type \
		{ \
		typedef boost::phoenix::detail::member_function_ptr<N, R, Member> member_function_type; \
		typedef boost::phoenix::detail::expression::function_eval< \
		member_function_type, \
		Expr, BOOST_PHOENIX_A(N) \
		> function_eval_type; \
		typedef typename function_eval_type::type base_type; \
		member_function(Member member, const Expr& expr, BOOST_PHOENIX_A_const_ref_a(N)) : \
		base_type(function_eval_type::make(member_function_type(member), expr, BOOST_PHOENIX_a(N))) {} \
		member_function(const member_function& other) : base_type(other) {} \
		};

		BOOST_PP_REPEAT_FROM_TO(1, BOOST_PHOENIX_COMPOSITE_LIMIT, GENERATE_MEMBER_FUNCTION, _)
#undef GENERATE_MEMBER_FUNCTION

			template <typename Type, typename Member, typename Expr>
		struct member_function_gen
		{

			member_function_gen(Member member_, const Expr& expr_) : member(member_), expr(expr_) {}

			Member member;
			const Expr& expr;

			member_function<Type(), Member, Expr> const operator()() const
			{
				return member_function<Type(), Member, Expr>(member, expr);
			}

#define GENERATE_FUNCTION_MEMBER_GEN_OPERATOR(_,N,__) \
	template <BOOST_PHOENIX_typename_A(N)> \
	member_function<Type(BOOST_PHOENIX_A(N)), Member, Expr> const operator()(BOOST_PHOENIX_A_const_ref_a(N)) const \
			{ \
			return member_function<Type(BOOST_PHOENIX_A(N)), Member, Expr> \
			(member, expr, BOOST_PHOENIX_a(N)); \
			}

			BOOST_PP_REPEAT_FROM_TO(1, BOOST_PHOENIX_COMPOSITE_LIMIT, GENERATE_FUNCTION_MEMBER_GEN_OPERATOR, _)
#undef GENERATE_FUNCTION_MEMBER_GEN_OPERATOR
		};

		template <typename Type, typename Member, typename Expr>
		struct member_function_placeholder_gen
		{

			member_function_placeholder_gen(Member member_, const Expr& expr_) : member(member_), expr(expr_) {}

			Member member;
			const Expr& expr;

			placeholder<Type, member_function<Type(), Member, Expr> > const operator()() const
			{
				return placeholder<Type, member_function<Type(), Member, Expr> >(member_function<Type(), Member, Expr>(member, expr));
			}

#define GENERATE_FUNCTION_MEMBER_PLACEHOLDER_GEN_OPERATOR(_,N,__) \
	template <BOOST_PHOENIX_typename_A(N)> \
	placeholder<Type, member_function<Type(BOOST_PHOENIX_A(N)), Member, Expr> > const operator()(BOOST_PHOENIX_A_const_ref_a(N)) const \
			{ \
			return placeholder<Type, member_function<Type(BOOST_PHOENIX_A(N)), Member, Expr> > \
			(member_function<Type(BOOST_PHOENIX_A(N)), Member, Expr>(member, expr, BOOST_PHOENIX_a(N))); \
			}

			BOOST_PP_REPEAT_FROM_TO(1, BOOST_PHOENIX_COMPOSITE_LIMIT, GENERATE_FUNCTION_MEMBER_PLACEHOLDER_GEN_OPERATOR, _)
#undef GENERATE_FUNCTION_MEMBER_PLACEHOLDER_GEN_OPERATOR
		};


		template <typename Type, typename Member, typename Expr>
		struct member_variable_placeholder : placeholder<Type, member_variable<Type, Member, Expr> >
		{
			member_variable_placeholder(Member member, const Expr& expr) :
			placeholder<Type, member_variable<Type, Member, Expr> >(member_variable<Type, Member, Expr>(member, expr)){}
		};

		template <typename Adapted, typename Type>
		struct get_member_ptr
		{
			typedef Type Adapted::*type;
		};

		template <typename Adapted, typename R>
		struct get_member_ptr<Adapted, R()>
		{
			typedef R(Adapted::*type)();
		};

#define GENERATE_GET_MEMBER_PTR(_,N,__) \
	template <typename Adapted, typename R, BOOST_PHOENIX_typename_A(N)> \
		struct get_member_ptr<Adapted, R(BOOST_PHOENIX_A(N))> \
		{ \
		typedef R(Adapted::*type)(BOOST_PHOENIX_A(N)); \
		};

		BOOST_PP_REPEAT_FROM_TO(1, BOOST_PHOENIX_COMPOSITE_LIMIT, GENERATE_GET_MEMBER_PTR, _)
#undef GENERATE_GET_MEMBER_PTR



			template <typename Type, typename Member, typename Expr, bool IsAdapted>
		struct selector;

		template <typename Type, typename Member, typename Expr>
		struct selector<Type, Member, Expr, false> //The type does not have a placeholder specialized
		{
			typedef member_variable<Type, Member, Expr> type;
		};


		template <typename Type, typename Member, typename Expr>
		struct selector<Type, Member, Expr, true>//The type does have a placeholder specialized
		{
			typedef member_variable_placeholder<Type, Member, Expr> type;
		};

		template <typename Type, typename Member, typename Expr>
		struct selector<Type(), Member, Expr, false>
		{
			typedef member_function_gen<Type, Member, Expr> type;
		};

		template <typename Type, typename Member, typename Expr>
		struct selector<Type(), Member, Expr, true>
		{
			typedef member_function_placeholder_gen<Type, Member, Expr > type;
		};


#define GENERATE_MEMBER_FUNCTION_SELECTOR(_,N,__) \
	template <typename Type, typename Member, BOOST_PHOENIX_typename_A(N), typename Expr> \
		struct selector<Type(BOOST_PHOENIX_A(N)), Member, Expr, false> \
		{ \
		typedef member_function_gen<Type, Member, Expr> type; \
		}; \
		template <typename Type, typename Member, BOOST_PHOENIX_typename_A(N), typename Expr> \
		struct selector<Type(BOOST_PHOENIX_A(N)), Member, Expr, true> \
		{ \
		typedef member_function_placeholder_gen<Type, Member, Expr > type; \
		};

		BOOST_PP_REPEAT_FROM_TO(1, BOOST_PHOENIX_COMPOSITE_LIMIT, GENERATE_MEMBER_FUNCTION_SELECTOR, _)
#undef GENERATE_MEMBER_FUNCTION_SELECTOR

	}



	template <typename Adapted, typename Type, typename Expr, bool IsAdapted = is_adapted<Type>::type::value>
	struct adapted : detail::selector<Type, typename detail::get_member_ptr<Adapted, Type>::type, Expr, IsAdapted>::type
	{
		typedef typename detail::selector<Type, typename detail::get_member_ptr<Adapted, Type>::type, Expr, IsAdapted>::type base_type;
		adapted(typename detail::get_member_ptr<Adapted, Type>::type member, const Expr& expr) :base_type(member, expr){}
	};
}

#define ADAPT_PHOENIX_PLACEHOLDER_FILLER_0(X, Y)                                \
	((X, Y)) ADAPT_PHOENIX_PLACEHOLDER_FILLER_1
#define ADAPT_PHOENIX_PLACEHOLDER_FILLER_1(X, Y)                                \
	((X, Y)) ADAPT_PHOENIX_PLACEHOLDER_FILLER_0
#define ADAPT_PHOENIX_PLACEHOLDER_FILLER_0_END
#define ADAPT_PHOENIX_PLACEHOLDER_FILLER_1_END

#define ADAPT_PHOENIX_MEMBER_INITIALIZATION_LIST(_,NAME,ELEM) \
	, BOOST_PP_TUPLE_ELEM(2, 1, ELEM)(&NAME::BOOST_PP_TUPLE_ELEM(2, 1, ELEM), *this)

#define ADAPT_PHOENIX_MEMBER_DECLARATION(_,NAME,ELEM) \
	adapted<NAME, BOOST_PP_TUPLE_ELEM(2, 0, ELEM), Expr> const BOOST_PP_TUPLE_ELEM(2, 1, ELEM);

#define ADAPT_PHOENIX_PLACEHOLDER( NAME, MEMBERS ) \
namespace adapt_phoenix { \
	template <> \
struct is_adapted<NAME> : boost::mpl::true_{}; \
	template <typename Expr> \
struct placeholder<NAME, Expr> \
	: Expr \
{ \
	placeholder(Expr const& base = Expr()) \
	: Expr(base) \
	BOOST_PP_SEQ_FOR_EACH(ADAPT_PHOENIX_MEMBER_INITIALIZATION_LIST, NAME, BOOST_PP_CAT(ADAPT_PHOENIX_PLACEHOLDER_FILLER_0 MEMBERS, _END)) \
{} \
	BOOST_PP_SEQ_FOR_EACH(ADAPT_PHOENIX_MEMBER_DECLARATION, NAME, BOOST_PP_CAT(ADAPT_PHOENIX_PLACEHOLDER_FILLER_0 MEMBERS, _END)) \
}; \
}

#endif

//END OF ADAPT_PHOENIX_PLACEHOLDER.HPP

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <iterator>

#include <boost/phoenix/phoenix.hpp>
namespace phx = boost::phoenix;


// In a header
struct foo
{
	char * a;
	char * c_str() { return a; }
};

// In a header
struct bar
{
	foo * X;

	bar(foo * _X) : X(_X) {}
};


ADAPT_PHOENIX_PLACEHOLDER(
	foo,
	(char*, a)
	(char*(), c_str)
)

	ADAPT_PHOENIX_PLACEHOLDER(
	bar,
	(foo*, X)
)
    

//if you don't want to define this function you can simply use 'phx:construct<std::string>'
template<typename Expr>
typename phx::expression::construct<phx::detail::target<std::string>, Expr >::type const
std_string(const Expr& expr)
{
	return phx::construct<std::string>(expr);
}

int main()
{
    
	foo foo1, foo2, foo3;
	foo1.a = "third";
	foo2.a = "second";
	foo3.a = "first";

	std::vector<bar> bars;
	bars.push_back(bar(&foo1));
	bars.push_back(bar(&foo2));
	bars.push_back(bar(&foo3));

	adapt_phoenix::placeholder<bar, phx::expression::argument<1>::type> const arg1; //or simply 'adapt_phoenix::arg1<bar> const arg1;'
	adapt_phoenix::arg2<bar> const arg2;

    std::cout << "Before sorting:" << std::endl;
	std::transform(bars.begin(), bars.end(), std::ostream_iterator<std::string>(std::cout, " "), 
                                                    std_string(arg1.X->c_str())
    );
	std::cout << std::endl;

	std::sort(bars.begin(), bars.end(),
		std_string(arg1.X->c_str()) < std_string(arg2.X->c_str())
    );
    
    std::cout << "After sorting:" << std::endl;
	std::transform(bars.begin(), bars.end(), std::ostream_iterator<std::string>(std::cout, " "), 
                                                    std_string(arg1.X->c_str())
    );
	std::cout << std::endl;
}
