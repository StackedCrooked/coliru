#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <type_traits>
#include <vector>

template<typename T>
class any {
public:
    explicit any(std::initializer_list<T> const& list)
        : data(list) { }

    template<typename InputIt>
    explicit any(InputIt begin, InputIt end)
        : data(begin, end) { }

    explicit operator typename std::enable_if<std::is_same<T, bool>::value, bool>::type() {
        return std::all_of(data.begin(), data.end(), [] (bool x) { return x; });
    }

private:
    std::vector<T> data;

    template<typename U>
    friend any<bool> operator==(U const& other, T const& self) {
        std::vector<bool> results(self.data.size());
        std::transform(self.data.begin(), self.data.end(), results.begin(),
                       [&] (T const& x) { return x == other; });
        return any(results.begin, results.end);
    }
};

int main() {
    auto x = 42;
    std::cout << static_cast<bool>(x == any<int>{3, 42, 90}) << '\n';
    std::cout << static_cast<bool>(x == any<int>{3, 41, 90}) << '\n';
    return 0;
}
