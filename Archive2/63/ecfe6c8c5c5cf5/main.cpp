#include <iostream>

class foo {
    static void do_nothing() {}
public:
    template<typename T = decltype(do_nothing)>
    void test(T fn = do_nothing){
        fn();
    }
};

int main() {
    foo f;
    f.test();
    f.test([]{std::cout << "Hello, World!\n";});
}
