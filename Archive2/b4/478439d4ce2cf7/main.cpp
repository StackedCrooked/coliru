#include <iostream>

class A {};

class B : public A {};

template <typename T>
class Template
{
public:
    Template() { std::cout << "Template default\n"; }
    Template(const Template &a) { std::cout << "Template copy constructor\n"; }

    template <typename T2>
    Template(const Template<T2> &a)
    {
       std::cout << "Templated template copy constructor\n";
    }
};

template <bool b, typename T = void>
struct my_enable_if {};
template <typename T>
struct my_enable_if<true, T> { typedef T type; };
template <typename Base, typename Derived>
struct my_is_base_of
{
    typedef char yes;
    typedef long no;    
    static yes test(Base*);    
    static no test(...);
    static const bool value = sizeof(test((Derived*)0)) == sizeof(yes);
};

template <typename T>
typename my_enable_if<my_is_base_of<A, T>::value>::type funcT(const Template<T>& a)
{
    std::cout << "Inside funcT(bt)\n";
}

int main()
{
    Template<B> bt;
    
    std::cout << "Calling funcT(bt)\n";
    
    funcT(bt);
}
