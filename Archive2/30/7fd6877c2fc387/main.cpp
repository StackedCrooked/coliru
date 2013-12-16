#include <type_traits>
#include <iterator>

template<typename T>
struct is_container_helper
{
  template<typename U,
           typename Require1 = decltype(std::begin(std::declval<const U&>())),
           typename Require2 = decltype(std::end(std::declval<const U&>()))>
    static std::true_type test(const U*);

  template<typename U>
    static std::false_type test(...);

  typedef decltype(test<T>(0)) type;
};

template<typename T>
struct is_container : is_container_helper<T>::type { };

#include <array>
#include <vector>

int main() {
    static_assert(!is_container<int>(),"int should not be a container");
    static_assert(is_container<std::vector<int>>(),"vector<int> should be a container");
    static_assert(is_container<std::array<int,13>>(),"array<int,N> should be a container");
    static_assert(is_container<int[13]>(),"int[N] should be a container");
}
