#include <iostream>

class Foo {
private:
    int v;
public:
    Foo(int val) : v(val) {}
    Foo(const Foo& other) 
        : v(other.v)
        { std::cout << "copy" << std::endl; }
    Foo operator+(const Foo& other) const { return Foo(v + other.v); }
    Foo& operator+=(const Foo& other) { v += other.v; return *this; }
    Foo operator-(const Foo& other) const { return Foo(v - other.v); }
    Foo& operator-=(const Foo& other) { v -= other.v; return *this; }
    
    Foo& operator=(const Foo& other) { std::cout << "assign" << std::endl; v = other.v; return *this; }
    friend std::ostream& operator<<(std::ostream& os, const Foo& f) { os << f.v; return os; }
};

int main()
{
    Foo a(6);
    Foo b(7); 
    Foo c(2);
    Foo d = a + b - c;
    std::cout << d << std::endl;
}