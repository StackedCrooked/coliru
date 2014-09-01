#include <iostream>


template <typename T>
T* Foo(T&& rval) {
    T* t = new T(rval);
    return t;    
}


int main() {
    volatile const bool _ = true;    
    bool* t = const_cast<bool*>(Foo(!_));
    
    std::cout << *t;
}