#include <iostream>

struct MyClass
{
    int i;
    
    MyClass operator+( MyClass const& m ) {
        return {m.i + i};
    }
    
    MyClass(int i) : i(i) {std::cout << "Ctor!\n";}
    MyClass(MyClass const&) {std::cout << "Copy-Ctor!\n";}
    ~MyClass() {std::cout << "* Dtor!\n";}
};

int main() {
    MyClass c{7}, b{3},
            a = b + c;
}