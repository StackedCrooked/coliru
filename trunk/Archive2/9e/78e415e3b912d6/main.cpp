#include <boost/utility/result_of.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/spirit/home/x3/support/utility/sfinae.hpp>


namespace boost { namespace spirit { namespace x3 { namespace detail
{
    template <typename Sig, typename Enable = void>
    struct is_callable_impl
      : mpl::false_
    {};

    template <typename F, typename... A>
    struct is_callable_impl<F(A...), typename disable_if_substitution_failure<
        typename result_of<F(A...)>::type>::type>
      : mpl::true_
    {};
}}}}

namespace boost { namespace spirit { namespace x3
{
    template <typename Sig>
    struct is_callable;

    template <typename F, typename... A>
    struct is_callable<F(A...)>
      : detail::is_callable_impl<F(A...)>
    {};
}}}


int main () { 

}