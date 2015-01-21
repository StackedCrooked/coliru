#include <iostream>
#include <memory>
 
template<class T>
struct Ptr {
    T* pad; // add pad to show difference between 'this' and 'data'
    T* data;
    Ptr(T* arg) : pad(nullptr), data(arg) 
    {
        std::cout << "Ctor this = " << this << std::endl;
    }
 
    ~Ptr() { delete data; }
    T** operator&() { return &data; }
};
 
template<class T>
void f(Ptr<T>* p) 
{
    std::cout << "Ptr   overload called with p = " << p << '\n';
}
 
void f(int** p) 
{
    std::cout << "int** overload called with p = " << p << '\n';
}
 
int main() 
{
    Ptr<int> p(new int(42));
    f(&p);                 // calls int** overload
    f(std::addressof(p));  // calls Ptr<int>* overload, (= this)
}