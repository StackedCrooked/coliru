#include <iostream>
using namespace std;

struct Printer{
    Printer(){
        std::cout << "Created\n";
    }
};

template<class Derived>
struct InitPrinter{
    static Printer p;
    InitPrinter() { (void)p; }
};

template<class Derived>
Printer InitPrinter<Derived>::p;

struct MyClass:InitPrinter<MyClass>{
     MyClass(){}
};

// Uncomment line below to print out created
//auto& p = MyClass::p;

int main() {}