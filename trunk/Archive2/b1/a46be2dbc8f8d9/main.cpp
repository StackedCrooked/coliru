struct pod {
    int i;
    char c;
};

#include <iostream>

int main() {
    pod foo;
    (void)foo;
    //std::cout << foo.i << '\n';//undefined
    
    //pod bar() not possible due to the most vexing parse
    //pod bar{};//c++11 solution for the most vexing parse
    pod bar = pod();
    std::cout << bar.i << '\n';//zero

    //pod baz = {0};//c idiom, all missing members are zero initialized
    pod baz = {};
    std::cout << baz.i << '\n';//zero
}
