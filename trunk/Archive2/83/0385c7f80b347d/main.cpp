#include <iostream>
#include <vector>
 
class foo {
    public:
        foo() {std::cout << "defctr" << std::endl;}
        foo(foo const &) {std::cout << "cpyctr" << std::endl;}
        ~foo() {std::cout << "dtr" << std::endl;}
        foo &operator=(foo const &) {std::cout << "op=" << std::endl; return *this;}
};

std::ostream &operator<<(std::ostream &os, foo const &) {
    return os << "foo" << std::endl;
}

template <typename T>
class byref_t {
    private:
        T &object;
    
    public:
        byref_t(T &object) : object(object) {}
        byref_t(byref_t const &other) : object(other.object) {}
        byref_t &operator =(byref_t const &other) {
            object = other.object;
            return *this;
        }
        
        T &operator *() {return object;}
        T *operator->() {return &object;}
        T &operator *() const {return object;}
        T *operator->() const {return &object;}
};

template <typename T>
byref_t<T> byref(T &t) {return byref_t<T>(t);}

int main() 
{
    
    foo f1, f2, f3, f4;
    
    for (auto &o: {byref(f1), byref(f2), byref(f3), byref(f4)}) {
        std::cout << *o << std::endl;   
    }
}