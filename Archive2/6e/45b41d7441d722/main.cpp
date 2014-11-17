#include <string>
#include <iostream>
 
struct A {
    int s;
    A() : s(0) {std::cout << "A()" << std::endl;}
    A(int num) : s(num) {std::cout << "A(int num)" << std::endl;}
    A(A & a){s=a.s;std::cout << "A(A& a)" << std::endl;}
    A(A && a){s=a.s;std::cout << "A(A&& a)" << std::endl;}
    A& operator + (A && a){ s=s+a.s; std::cout << "operator +" << std::endl;return *this; }
    
    
    ~A(){std::cout << "~A()" << std::endl;}
};
 
A fun(A& a){
    std::cout << "before return in fun()" <<std::endl;
    return a;    

}
 
int main()
{
    A a(100);
    A &&b = fun(a);
    
    std::cout<< "b.s=" << b.s <<std::endl;
}