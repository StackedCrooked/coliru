#include <initializer_list>
#include <iterator>
#include <stdexcept>
#include <utility>

template<class T, int N>
struct wrapper {
  T data[N];

  constexpr wrapper(int s);         // a
  constexpr wrapper(int j, int k);  // b

  constexpr wrapper(std::initializer_list<T> v) : wrapper(std::make_index_sequence<N>{}, v) {} // c
private:
  constexpr static T too_short(std::true_type) { return {}; }
  T too_short(std::false_type) { throw std::invalid_argument("braced-init-list too short"); }
  template<std::size_t... Is> constexpr wrapper(std::index_sequence<Is...>, std::initializer_list<T> v)
    : data{v.size() > Is ? v.begin()[Is] : too_short(std::is_default_constructible<T>{})...} {}
};

struct X { int i; constexpr X(int i) : i(i) {} };

int main() {
    static_assert(wrapper<X, 1>{42}.data[0].i == 42, "!!");
    constexpr int j = wrapper<X, 5>{42}.data[0].i;  // fails - braced-init-list too short
}