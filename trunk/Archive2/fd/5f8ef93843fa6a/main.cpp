#include <numeric>
#include <iterator>
#include <type_traits>


template <typename Container, typename... T_Args>
decltype (std::accumulate(
    std::declval<typename std::remove_reference<Container>::type::iterator>(),
    std::declval<typename std::remove_reference<Container>::type::iterator>(),
    std::declval<T_Args>()...
))
reduce (Container&& x, T_Args&&... arg) {
    return std::accumulate (std::begin(x),  std::end(x),
                            std::forward<T_Args>(arg)...);
}

template <typename... T>
struct foo;

#include <vector>
#include <iostream>

using std::endl;
using std::cout;

int mul(int a, int b) {
    return (1 + a) * b;
}

int main()
{
    std::vector<int> v = { 1, 2, 3, 4, 5 };
    std::vector<int> const& vcr = v;

    cout         << reduce (v, 0);
    cout << endl << reduce (vcr, 0);
    cout << endl << reduce (std::vector<int> { 1, 2, 3, 4, 5 }, 0);
    cout << endl << reduce (v, 0, mul);
    cout << endl << reduce (vcr, 0, mul);
    cout << endl << reduce (std::vector<int> { 1, 2, 3, 4, 5 }, 0, mul);
    cout << endl;
}