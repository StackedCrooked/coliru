#include <ios>
#include <iostream>
#include <type_traits>                  // is_same, is_base_of
#include <boost/mpl/end.hpp>            // end
#include <boost/mpl/find_if.hpp>        // find_if
#include <boost/mpl/lambda.hpp>         // lambda
#include <boost/mpl/logical.hpp>        // not_
#include <boost/mpl/placeholders.hpp>   // _1
#include <boost/mpl/vector.hpp>         // vector

template<typename Sequence, typename Pred>
struct all_of
:
        std::is_same< typename
                boost::mpl::find_if<
                        Sequence,
                        boost::mpl::not_<Pred>
                >::type, typename
                boost::mpl::end<Sequence>::type
        >
{};

template<typename Sequence, typename Pred>
struct none_of
:
        all_of< Sequence, boost::mpl::not_< Pred > >
{};

template<typename Sequence, typename Pred>
struct any_of
:
        boost::mpl::not_< none_of< Sequence, Pred > >
{};

struct B {}; 
struct D : B {};
struct X {};

using Universe = boost::mpl::vector<B, D, X>;
using Predicate = boost::mpl::lambda<std::is_base_of<B, boost::mpl::_1>>;

int main()
{
    std::cout << std::boolalpha;
    std::cout << all_of<Universe, Predicate>{} << "\n";
    std::cout << any_of<Universe, Predicate>{} << "\n";
}
