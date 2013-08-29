int f(int) {return 0;}
double f(double id) {throw id;}

struct C{ 
    int i;
    double d;
 C(int ii, double id);
};
    
C::C(int ii, double id)
try : i(f(ii)), d(id) {
    // constructor statements
}
catch (...) {
    // handles exceptions thrown from the ctor-initializer
    // and from the constructor statements
}

#include <iostream>
int main() {
    C c(3, 4);
    std::cout << "works fine";
}