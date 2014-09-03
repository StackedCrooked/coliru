#include <iostream>

//class X;
//X operator+(X,X);

class Y {};
class X {
public:    
    X(int i): _i(i) {}    
    X(Y):X(103){}
    friend X operator+(X a, X b) { return a._i + b._i; }
    void print() { std::cout << _i << '\n'; }
private:
    int _i;
};

void f() {
   Y y1, y2;
   (y1 + y2).print();                         // error, no operator+ takes two Y
   X x1(1); 
   (x1 + y1).print();                         // OK, ADL can find it
}

int main()
{
    f();
}