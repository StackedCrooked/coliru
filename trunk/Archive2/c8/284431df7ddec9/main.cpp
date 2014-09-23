#include <iostream>
#include <type_traits>

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

template <typename T>
auto funcT(const Template<T>& a) -> typename std::enable_if<std::is_base_of<A, T>::value>::type
{
}

int main()
{
    Template<B> bt;
    
    std::cout << "Calling funcT(bt)\n";
    
    funcT(bt);
}
