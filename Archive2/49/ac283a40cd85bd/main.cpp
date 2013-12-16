#include <iostream>
#include <string>
#include <vector>

class Foo{
public:
    Foo & operator[](int i) {
        std::cout << "Non-Const" << std::endl;
        return *this;
    }
    
    const Foo& operator[](int i) const {
        std::cout << "Const" << std::endl;
        return *this;
    }
    
    Foo& operator = (const Foo& f) {
        return *this;
    }
};

void test(const Foo&){}

int main()
{
    Foo f1;
    test(f1[0]);
    f1[0] = Foo();
    
    const Foo f2;
    test(f2[0]);
    //f2[0] = Foo();
}
