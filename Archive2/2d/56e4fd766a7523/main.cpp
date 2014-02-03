#include <iostream>

class foo {
    static constexpr auto empty_lambda = []{};
public:
    template<typename T = decltype(empty_lambda)>
    void test(T fn = empty_lambda){
        fn();
    }
};

constexpr decltype(foo::empty_lambda) foo::empty_lambda;

int main() {
    foo f;
    f.test();
    f.test([]{std::cout << "Hello, World!\n";});
}
