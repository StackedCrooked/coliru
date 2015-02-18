#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/apply.hpp>
#include <iostream>
#include <utility>
#include <stdexcept>
#include <functional>

namespace mpl = boost::mpl;


template <typename OP, typename T, typename OP_T = typename mpl::apply<OP, T>::type>
struct apply_if_ok: OP_T {

    template <typename...Args, typename R = std::result_of_t<OP_T(Args...)>>
    R operator()(Args&&...args) const {
        return static_cast<OP_T>(*this)(std::forward<Args>(args)...);
    }
    template <typename...Args>
    auto operator()(...) const {
        // throw std::runtime_error("Invalid arguments");
        return "Invalid arguments";
    }
};


int main() {
    using OP = std::plus<mpl::_>;
    int i = 3;

    auto n1 = apply_if_ok<OP, void>()(1, 2);
    std::cout << "plus (1, 2) = " << n1 << std::endl;

    auto n2 = apply_if_ok<OP, void>()(1, &i);
    std::cout << "plus (1, *) = " << n2 << std::endl;

    auto n3 = apply_if_ok<OP, int>()(&i, &i);
    std::cout << "plus (*, *) = " << n3 << std::endl;

    auto n4 = apply_if_ok<OP, void>()(&i, &i);
    std::cout << "plus (*, *) = " << n4 << std::endl;
}
