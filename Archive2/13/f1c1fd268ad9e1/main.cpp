#include <iostream>
#include <vector>
 
class foo {
    public:
        foo() {std::cout << "defctr" << std::endl;}
        foo(foo const &) {std::cout << "cpyctr" << std::endl;}
        ~foo() {std::cout << "dtr" << std::endl;}
        foo &operator=(foo const &) {std::cout << "op=" << std::endl; return *this;}
};

std::ostream &operator<<(std::ostream &os, foo const &) {
    return os << "foo" << std::endl;
}

int main() 
{
    
    foo f1, f2, f3, f4;
    
    for (auto &&o: {f1, f2, f3, f4}) {
        std::cout << o << std::endl;   
    }
}