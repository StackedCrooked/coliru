#include <iostream>

struct Base {
    Base() {
        std::cout << "Inside the compound-statement of Base()\n";
        throw "Hello World!\n";
    }
};

struct Derived : Base{
    Derived()
    try : Base()
    {
        std::cout << "Inside the compound-statement of Derived()\n";
    }
    catch(char const* p)
    {
        std::cout << "Inside the catch-clause of the function-try-block of Derived()\n";
        std::cout << "Caught message: " << p;
    }
};

int main()
{
    try { Derived d; }
    catch(...){ std::cout << "Inside the catch-clause inside main\n"; }
}