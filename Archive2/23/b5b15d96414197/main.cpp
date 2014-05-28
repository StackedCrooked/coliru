#include <iostream>

template<class T>
[[noreturn]] T no_ret() {}

template<int... I>
struct f
{
    int operator()(int a) {
        try {
            return (*this)(a);
        } catch (int& r) {
            return r;
        }
    }
    
    int op(int a) {
        int result=0;
        bool b[] = { a==I ? (result=a,true): true ...};
        (void)b;
        return result;
    }
};

int main() {
    auto fun=f<0,1>();
    std::cout << fun(-1) << std::endl;
    std::cout << fun(0) << std::endl;
    std::cout << fun(1) << std::endl;
    std::cout << fun(2) << std::endl;
    return 0;
}