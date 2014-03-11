#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <type_traits>
#include <vector>

template<typename T>
class any_t{
public:
    explicit any_t(std::initializer_list<T> const& list)
        : data(list) { }

    template<typename InputIt>
    explicit any_t(InputIt begin, InputIt end)
        : data(begin, end) { }

    template<class U = T>
    explicit operator typename std::enable_if<std::is_same<U, bool>::value, bool>::type() {
        return std::any_of(data.begin(), data.end(), [] (bool x) { return x; });
    }

private:
    std::vector<T> data;

    template<typename U>
    friend any_t<bool> operator==(U const& other, any_t const& self) {
        std::vector<bool> results(self.data.size());
        std::transform(self.data.begin(), self.data.end(), results.begin(),
                       [&] (T const& x) { return x == other; });
        return any_t<bool>(results.begin(), results.end());
    }
};

struct deduce;
template<class T, class U>
using Defaulted = typename std::conditional<std::is_same<T, deduce>::value, U, T>::type;

template<class T = deduce, class U, class... Us, class R = Defaulted<T, U>>
any_t<R> any(U u, Us... us){
    return any_t<R>{static_cast<R>(u), static_cast<R>(us)...};
}

int main() {
    auto x = 42;
    std::cout << bool(x == any<long>(3, 42, 90)) << '\n';
    std::cout << bool(x == any(3, 41, 90)) << '\n';
    return 0;
}
