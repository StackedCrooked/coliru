template<class T> auto val_of(const T* t,int) -> decltype(t->val()) {return t->val();}
template<class T> int val_of(const T*,...) {return 0;}
template<class T> int val_of(const T& t) {return val_of(&t, 0);}

struct A { int val() const { return 1; } };
struct B { int val() const { return 2; } };
struct C {  };

#include <iostream>
int main() {
    A a;
    B b;
    C c;
    std::cout << val_of(a) << val_of(b) << val_of(c);
}
    
