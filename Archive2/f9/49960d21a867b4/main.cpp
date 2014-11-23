#include <string>
#include <iostream>

using namespace std;

class B {
     public:
     B() { cout << "B:-\n"; }
     B(int i) { cout << "B:int\n"; }
     B(float i) { cout << "B:float\n"; }
};

class D : public B {
     using B::B;
     public:
     D(double i) : B() { cout << "D:double\n"; }
};

class D2 : public B {
     using B::B;
     public:
     D2(float i) : B() { cout << "D:float\n"; }
};

class D3 : public B {
     using B::B;
     public:
     D3(float i) = delete;
};

int main() {
    D a{5};    // B:int
    D b{5.f};  // B:float
    D c{5.};   // B:- D:double
    
    D2 d{5.f}; // B:- D:float
    
    //D3 e{5.f}; // error: use of deleted function 'D3::D3(float)'
}