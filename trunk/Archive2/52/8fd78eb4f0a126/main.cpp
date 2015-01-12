#include <array>
#include <iostream>
#include <string>
#include <functional>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/fusion/functional/invocation/invoke.hpp>
#include <boost/fusion/container/vector.hpp>
#include <boost/fusion/adapted/mpl.hpp>
#include <boost/fusion/include/mpl.hpp>
#include <boost/variant.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/timer/timer.hpp>

template<typename T>
struct fit : std::remove_volatile<T>
{};

namespace result_of
{
template<typename S>
struct dynamic_at_c : boost::make_variant_over<
    typename boost::mpl::transform<
        S
      , boost::mpl::lambda<fit<boost::mpl::_>>
    >::type
> {};
} // result_of

template<typename T>
struct construct_array
{
    template<typename... Ts>
    auto operator()(Ts&&... ts) -> std::array<T, sizeof...(Ts)>
    {
        return std::array<T, sizeof...(Ts)>{ts...};
    }
};

template<typename S>
auto dynamic_at_c(const S& seq, std::size_t idx)
    -> typename result_of::dynamic_at_c<S>::type
{
    return boost::fusion::invoke(construct_array<typename result_of::dynamic_at_c<S>::type>(), seq).at(idx);
}

struct printer : boost::static_visitor<void>
{
    template<typename T>
    void operator()(const T& val) const
    {
        std::cout << val << std::endl;
    }
};

int main(int argc, char* argv[])
{
    boost::fusion::vector<int, std::string> vec(1, "one");
    auto idx0 = dynamic_at_c(vec, 0);
    auto idx1 = dynamic_at_c(vec, 1);
    boost::apply_visitor(printer(), idx0);
    boost::apply_visitor(printer(), idx1);

return 0;
}
