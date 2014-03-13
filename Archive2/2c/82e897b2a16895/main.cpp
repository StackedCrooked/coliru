#include <boost/mpl/transform.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/pair_view.hpp>
#include <boost/mpl/vector.hpp>
#include <vector>
#include <map>
 
namespace mpl = boost::mpl;

namespace detail
{
    using namespace mpl;

    template <template <typename...> class Container, typename... T>
        using unary = typename transform<vector<T...>, Container<_1> >::type;

    namespace binary_impl
    {
        template <typename MplVector> struct pairs;

        template <> struct pairs<mpl::vector<> >
        {
            using type = mpl::vector<>;
        };

        template <typename A, typename B, typename... T>
            struct pairs<mpl::vector<A, B, T...> >
        {
            using type = typename mpl::push_front<
                    typename pairs<mpl::vector<T...> >::type,
                    mpl::pair<A, B>
                >::type;
        };
    }

    template <template <typename...> class Container, typename... T>
        using binary = typename transform<
            typename binary_impl::pairs<vector<T...> >::type, 
            Container<apply_wrap1<first<>, _1>, apply_wrap1<second<>, _1> >
            >
            ::type;
}

template <typename K, typename V, typename stuff = std::less<K> >
struct MyMap : std::map<K,V,stuff> { using std::map<K, V>::map; };

template <typename... T> using make_vectors = detail::unary<std::vector, T...>;
template <typename... T> using make_pairs   = detail::binary<std::pair,  T...>;
template <typename... T> using make_mymaps  = detail::binary<MyMap,      T...>;

#include <iostream>
#include <string>

int main()
{
    auto vectors = make_vectors<int, char, double> { };
    auto pairs   = make_pairs  <int, char, int, std::string, int, double> { };
    auto mymaps  = make_mymaps <int, char, int, std::string, int, double> { };
}
