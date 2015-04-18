#include <iostream>

struct S;

void bar(void (S::*& f)() ) {
    std::cout << "lvalue" << std::endl;
}
void bar(void (S::*&& p)() ) {
    std::cout << "rvalue" << std::endl;
}

struct S {
    void foo() { }  
};

int main() {
    void (S::*f)();
    
    bar(f);
    bar(&S::foo);
}