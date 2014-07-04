#include <boost/mpl/string.hpp>

template<int N>
struct mpl_string_impl {
    using type = typename boost::mpl::push_back<typename mpl_string_impl<N/10>::type, typename boost::mpl::char_<N%10 + '0'>::type>::type;
};

template<>
struct mpl_string_impl<0> {
    using type = boost::mpl::string<>;  
};

template<int N>
using mpl_string = typename mpl_string_impl<N>::type;

int main() {
    static_assert(std::is_same<mpl_string<42>, boost::mpl::string<'42'>::type>::value, "");
}