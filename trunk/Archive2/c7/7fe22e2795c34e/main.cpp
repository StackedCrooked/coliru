#include <iterator>
#include <utility>
#include <type_traits>

namespace detail
{
    using std::begin;    
    template <typename T, typename = void>
    struct has_begin : std::false_type {};
    template <typename T>
    struct has_begin<T, decltype(void(begin(std::declval<T&>())))> : std::true_type {};
    
    using std::end;
    template <typename T, typename = void>
    struct has_end : std::false_type {};
    template <typename T>
    struct has_end<T, decltype(void(end(std::declval<T&>())))> : std::true_type {};
}

template <typename T> using has_begin = detail::has_begin<T>;
template <typename T> using has_end = detail::has_end<T>;

// Target:
template <typename ContainerType>
void sort(ContainerType& container)
{
    static_assert(has_begin<ContainerType>{} && has_end<ContainerType>{}, "Invalid container type");
}

// Tests:
#include <vector>
#include <list>

namespace X
{
    struct A {};
    
    A* begin(A&) { return {}; }
    A* end(A&) { return {}; }
}

struct B {};

int main()
{
    std::vector<int> v; sort(v);  // OK
    std::list<int> l; sort(l);    // OK
    X::A a; sort(a);              // OK
    int arr[3]{}; sort(arr);      // OK
    B b; sort(b);                 // error: Invalid container type
}
