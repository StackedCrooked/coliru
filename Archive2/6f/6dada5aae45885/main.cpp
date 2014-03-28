#include <iostream>
#include <type_traits>
 
struct A {
    int m;
};
 
struct B {
    int m1;
private:
    int m2;
};
 
struct C {
    virtual void foo();
};

class D {
public:
    int l = 5;
    static D create(int val) {
        D res;
        res.l = val;
        return res;
    }
    int do_nothing() {return l;};
};
 
int main()
{
    D foo;
    
    std::cout << std::boolalpha;
    std::cout << std::is_pod<D>::value << '\n';
    std::cout << foo.l  << '\n';
}