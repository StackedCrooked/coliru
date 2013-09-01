#include <iostream>
#include <typeinfo>

#include <boost/utility.hpp>

#include <boost/mpl/apply.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>

#include <boost/mpl/plus.hpp>

namespace mpl=boost::mpl;


template <typename T, typename Enable=void>
struct is_apply_able : mpl::false_
{};

template <typename T>
struct is_apply_able<T,typename boost::enable_if<mpl::is_lambda_expression<T> >::type> : mpl::true_
{};
BOOST_MPL_HAS_XXX_TEMPLATE_NAMED_DEF(is_metafunction_class, apply, false)
template <typename T>
struct is_apply_able<T,typename boost::enable_if<is_metafunction_class<T> >::type> : mpl::true_
{};

struct plus_two
{
    template <typename Number>
	struct apply
	{
		typedef typename mpl::plus<Number,mpl::int_<2> >::type type;
	};
};

template <typename T>
struct Foo
{};

template <typename Partial, typename T>
struct maybe_apply
: mpl::eval_if<is_apply_able<Partial>,
    mpl::apply<Partial, T>,
    mpl::identity<Partial> > 
{ };

int main()
{
	std::cout << typeid(maybe_apply<Foo<mpl::_1>,int>::type).name() << std::endl;
	std::cout << typeid(maybe_apply<plus_two,mpl::int_<1> >::type).name() << std::endl;
	std::cout << typeid(maybe_apply<Foo<float>,int>::type).name() << std::endl;
}