#include <iostream>

class Foo
{
public: 
    ~Foo() {
        std::cout << "Destructor called\n";
    }

    const Foo& operator=(const Foo&) {
        std::cout << "Assignment called\n";
        return *this;
    }
};

Foo foo()
{
    return Foo();
}

int main()
{
    foo();
}