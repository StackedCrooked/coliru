#include <iostream>

struct one {
    one() { std::cout << "one\n"; }
};

struct two {
    two() { std::cout << "two\n"; }
};

struct foo {
    int i;
    union u {
        struct init_one { };
        struct init_two { };
        
        one x;
        two y;
        
        u(init_one) : x{} { }
        u(init_two) : y{} { }
    } u;
};

int
main() {
    foo a{3, {foo::u::init_one{}}};
    foo b{4, {foo::u::init_two{}}};
    
    (void) a;
    (void) b;
}
