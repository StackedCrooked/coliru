#include <iterator>
#include <type_traits>
#include <utility>

using std::begin;
using std::end;

template<typename T>
using Unqualified = typename std::remove_cv<typename std::remove_reference<T>::type>::type;

struct has_iterators_impl {
    template<typename T, 
                         typename B = decltype(begin(std::declval<T>())),
                         typename E = decltype(end(std::declval<T>()))>
    static std::true_type test(int);
    template<typename...>
    static std::false_type test(...);
};

template<typename T>
using has_iterators = decltype(has_iterators_impl::test<T>(0));

template<typename T>
void print() {
    int x;
}

int main() {
    const char x[] = "hello";
    using y = decltype(x);
    using z = decltype(x);
    print<z>();
    print<decltype(std::declval<z>())>();
    print<decltype(begin(std::declval<z>()))>();
    print<decltype(end(std::declval<z>()))>();
    print<has_iterators<y>>();
    static_assert(has_iterators<y>{}, "..");
}