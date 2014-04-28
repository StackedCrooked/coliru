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
    typename std::enable_if<std::is_void<U>::value, int>::type test(int) override { return 0; }
    template<typename U = T>
    typename std::enable_if<!std::is_void<U>::value, int>::type test(int) override { return 1; }
    
    int test(int) { return test<>(0); }
};

template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return nullptr;
}

int main() {
    std::unique_ptr<base> x = make_unique<derived<int>>();
}