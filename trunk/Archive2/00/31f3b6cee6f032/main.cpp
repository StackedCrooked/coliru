#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <type_traits>
#include <vector>

template<typename T>
class any;

namespace detail {
    template<typename T>
    class any_base {
    public:
        explicit any_base(std::initializer_list<T> const& list)
            : data(list) { }

        template<typename InputIt>
        explicit any_base(InputIt begin, InputIt end)
            : data(begin, end) { }

        std::vector<T> data;
    };
}

template<typename T>
class any : public detail::any_base<T> {
public:
    using detail::any_base<T>::any_base;
};

template<>
class any<bool> : public detail::any_base<bool> {
public:
    using detail::any_base<bool>::any_base;

    explicit operator bool() {
        return std::any_of(data.begin(), data.end(), [] (bool x) { return x; });
    }
};

template<typename U, typename T>
any<bool> operator==(U const& other, any<T> const& self) {
    std::vector<bool> results(self.data.size());
    std::transform(self.data.begin(), self.data.end(), results.begin(),
                   [&] (T const& x) { return x == other; });
    return any<bool>(results.begin(), results.end());
}

int main() {
    auto x = 42;
    std::cout << static_cast<bool>(x == any<int>{3, 42, 90}) << '\n';
    std::cout << static_cast<bool>(x == any<int>{3, 41, 90}) << '\n';
    return 0;
}
