#include <iostream>
#include <memory>
#include <type_traits>

struct base {
    virtual ~base() = default;
    virtual int test(int) = 0;
};

template<typename T>
struct derived : public base  {
    template<typename U = T>
    typename std::enable_if<std::is_void<U>::value, int>::type test(int) { return 0; }
    template<typename U = T>
    typename std::enable_if<!std::is_void<U>::value, int>::type test(int) { return 1; }
};

template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return { new T(std::forward<Args>(args)...) };
}

int main() {
    std::unique_ptr<base> x = make_unique<derived<int>>();
}