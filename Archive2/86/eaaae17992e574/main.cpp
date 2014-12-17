#include <iostream>

template <class T> struct tag {};

template <class T>
class B { };

template <class T>
class A {
public:    
    void f()
    {
        f(tag<T>());
    }
    
private:
    template <typename U>
    void f(tag<B<U>>)
    {
        std::cout << "A<B<U>>\n";
    }
    
    template <typename U>
    void f(tag<U>)
    {
        std::cout << "A<U>\n";
    }
};

int main()
{
    A<B<int>> ab;ab.f();
    A<int> ai;ai.f();
}
