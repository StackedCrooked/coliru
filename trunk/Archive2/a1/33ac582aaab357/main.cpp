#include <iterator>
#include <utility>
#include <type_traits>
namespace detail
{
    using std::begin;
    using std::end;    
    template <typename T> static auto has_begin(int) -> decltype(void(begin(std::declval<T&>())), std::true_type());
    template <typename T> static auto has_begin(...) -> std::false_type;
    template <typename T> static auto has_end(int) -> decltype(void(end(std::declval<T&>())), std::true_type());
    template <typename T> static auto has_end(...) -> std::false_type;
}

template <typename T> using has_begin = decltype(detail::has_begin<T>(0));
template <typename T> using has_end = decltype(detail::has_end<T>(0));

template <typename ContainerType>
void sort(ContainerType& container)
{
    static_assert(has_begin<ContainerType>{} && has_end<ContainerType>{}, "Invalid container type");
}

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
    B b; sort(b);                 // error: Invalid container type
}
