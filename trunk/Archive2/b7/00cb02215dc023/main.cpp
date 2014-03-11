#include <iostream>
#include <string>
#include <vector>
#include <memory>


template <class T> struct checked_ptr : T 
{
    using T::T; 
    auto operator*() -> decltype(this->T::operator*()) {
        if (!(*this)) 
            throw std::logic_error{"fuck"}; 
        return T::operator*();
    }
}; 

template <class T> struct checked_ptr<T*>
{
    T& operator*() {
        if (!t) 
            throw std::logic_error{"fuck"}; 
        return *t;
    }
    T* t;
}; 

int main() {
    std::shared_ptr<int> x = 0; 
    std::shared_ptr<int> z{new int}; 
    checked_ptr<std::shared_ptr<int>> cp{z}; 
    *cp;
    int* x2 = 0;
    int* z2 = new int{};
    checked_ptr<int*> cp2{z2};
    *cp2;
}