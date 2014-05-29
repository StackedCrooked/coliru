#include <type_traits>

template<typename T>
using unqualified_one = typename std::remove_reference<typename std::remove_cv<T>::type>::type;

template<typename T>
using unqualified_two = typename std::remove_cv<typename std::remove_reference<T>::type>::type;

template<typename T, typename U = unqualified_one<T>, typename V = unqualified_two<T>>
void stacktrace() {
    static_assert(std::is_same<U, int>::value, "..."); // wtf?
    static_assert(std::is_same<V, int>::value, "...");
}

int main() {
    stacktrace<const int&>();
}