#include <iostream>
#include <string>

struct Base1 {
    Base1() : a(1) {}
    int a;
};

struct Base2 {
    Base2() : b(2) {}
    int b;
};

struct Derived : Base2, Base1 {
    Derived() : c(3) {}
    int c;
    void f(int n) { std::cout << n << ", " << a << ", " << b << ", " << c << ", " << '\n'; }
};
int main()
{
    void (Derived::* pd)(int) = &Derived::f;
    void (Base1::* pb)(int) = static_cast<void (Base1::*)(int)>(pd);
    void (Base2::* pc)(int) = static_cast<void (Base2::*)(int)>(pd);
    void (Base2::* px)(int) = pd; // It is a tradgedy this cannot be done
 
    Derived d;
    (d.*pb)(0);
    (d.*pc)(0);
    
    Base1 b;
    (b.*pb)(4); // Undefined behavior
    
    Base2 c;
    (c.*pc)(5); // Undefined behavior
}

