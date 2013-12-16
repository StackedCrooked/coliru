#include <istream>
 
class A : private std::istream {
public:
    A() : std::istream(NULL) { }
};
 
class B : public A, private std::ios {
public:
    B() : A() { }
};
 
int main () {}