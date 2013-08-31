#include <iostream>

class A {
     public:
     int i;
     inline A() : i() {}
     
};

int main(int argc, char** argv) {
    A a;
    //A b(); //This is not valid, the compiler thinks it's a function declaration
             //http://stackoverflow.com/a/877538/2436175
    A c = A();
    std::cout << a.i << " " << c.i << std::endl;
    }

