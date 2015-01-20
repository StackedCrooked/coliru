#include <string>
#include <iostream>

class A {}; class B {}; class C {}; class D {};

template<typename T> struct traits { };
template<> struct traits<A> { static std::string code() {return "class A";}};
template<> struct traits<B> { static std::string code() {return "class B";}};
template<> struct traits<C> { static std::string code() {return "class C";}};
template<> struct traits<D> { static std::string code() {return "class D";}};

template<typename T>
struct RegisterClass
{
    static RegisterClass instance;
    RegisterClass()
    {
        std::cout << "Registering " << traits<T>::code() << '\n';
    }
    static RegisterClass& doRegister() { return instance; }
};
template<typename T>
RegisterClass<T> RegisterClass<T>::instance;

template<typename T> void printMe() {
    RegisterClass<T>::doRegister();
    std::cout << "Printing " << traits<T>::code() << '\n';
}

int main(void)
{
    printMe<B>(); 
    printMe<B>(); 
    printMe<C>(); 
    return 0;
}