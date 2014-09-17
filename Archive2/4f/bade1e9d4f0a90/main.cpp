#include <string>
#include <iostream>

class A {
public:
    virtual void f(const std::string& s, bool thing = true) {
        if(thing) {
            std::cout << "got " << s << std::endl;
        }
        else {
            std::cout << "thing was false" << std::endl;
        }
    
    }
    virtual ~A() {}
};

class B : public A{ };

int main() {
    B b;
    b.f("wow");
}
