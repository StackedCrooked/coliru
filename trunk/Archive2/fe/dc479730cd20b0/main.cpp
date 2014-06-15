#include <type_traits>
#include <iostream>

template <class ...T> struct common_type;
 
template <class T>
struct common_type<T> {
    typedef typename std::decay<T>::type type;
};
 
template <class T, class U>
struct common_type<T, U> {
    typedef typename std::decay<decltype(true ? std::declval<T>() : std::declval<U>())>::type type;
};
 
template <class T, class U, class... V>
struct common_type<T, U, V...> {
    typedef typename common_type<typename common_type<T, U>::type, V...>::type type;
};

int main() {
    std::cout << std::is_same<std::common_type<int&, const int&>::type, int>::value;
}