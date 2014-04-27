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

int main() {
    std::shared_ptr<base> x = std::make_shared<derived<int>>();
    std::cout << x->test(0) << '\n';
    x = std::make_shared<derived<void>>();
    std::cout << x->test(0) << '\n';
}