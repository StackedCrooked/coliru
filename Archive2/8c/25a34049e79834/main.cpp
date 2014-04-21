#include <boost/any.hpp>
#include <functional>
#include <tuple>
#include <utility>
#include <vector>

namespace detail {
    template<typename F>
    class memoization {
    public:
        explicit memoization(F function) : function(std::move(function)) { }

        template<typename... Args>
        auto operator()(Args&&... args) const -> decltype(std::declval<F>()(std::forward<Args>(args)...)) {
            auto tuple = std::make_tuple(std::forward<Args>(args)...);
            for (auto& entry : entries) {
                if (std::get<2>(entry)(tuple)) {
                    return boost::any_cast<decltype(std::declval<F>()(std::forward<Args>(args)...))>(std::get<0>(entry));
                }
            }
            auto value = function(std::forward<Args>(args)...);
            entries.emplace_back(value, tuple, [=] (boost::any value) {
                try {
                    return boost::any_cast<decltype(tuple)>(value) == tuple;
                } catch (boost::bad_any_cast const&) {
                    return false;
                }
            });
            return value;
        }

    private:
        mutable std::vector<std::tuple<boost::any, boost::any, std::function<bool(boost::any)>>> entries;
        F function;
    };
}

template<typename F>
detail::memoization<F> memoize(F function) {
    return detail::memoization<F>(std::move(function));
}

#include <cstdlib>
#include <iostream>

int main() {
    auto f = memoize([] (int n) { return n + std::rand(); });
    for (auto i = 0; i < 10; ++i) {
        std::cout << f(i) << '\n';
        std::cout << f(i) << '\n';
        std::cout << f(i) << '\n';
    }
    return 0;
}
