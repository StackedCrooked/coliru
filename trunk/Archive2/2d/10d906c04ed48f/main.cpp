#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>

template <class T>
class TypeInfo 
{
 public:
 static size_t getType()
 {
    return typeid(T).hash_code();
 }
};

class A : public TypeInfo<A>
{
    
};

class B : public A, public TypeInfo<B>
{
public: 
    using TypeInfo<B>::getType;

};

int main()
{
    A a;
    B b;
    
    std::cout << a.getType() << std::endl;
    std::cout << b.getType() << std::endl;
    std::cout << A::getType() << std::endl;
    std::cout << B::getType() << std::endl;
    
}
