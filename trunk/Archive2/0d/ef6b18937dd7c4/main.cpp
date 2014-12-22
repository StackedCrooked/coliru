#include <iostream>
#include <string>
#include <vector>

struct A
{
    int value = 10;
    
    A()
    {
        std::cout << "A ctor value = " << value << std::endl; 
    }
    
    virtual void setValue(int p_value)
    {
        value = p_value;
        std::cout << "A::setValue p_value = " << p_value  << std::endl; 
    }
};

struct B : A
{
    int value    = 30;
    int valueExt = 20;
    
    B() : A()
    {
        std::cout << "B ctor value = " << value << std::endl; 
        std::cout << "B ctor valueExt = " << valueExt << std::endl; 
    }
    
    virtual void setValue(int p_value) override
    {
        std::cout << "B::setValue p_value = " << p_value << std::endl; 
        A::setValue(p_value);
    }
};

int main()
{
    B myObjB;
    myObjB.setValue(50);
    std::cout << "myObjA.value = " << ((A*)&myObjB)->value << std::endl; 
    std::cout << "myObjB.value = " << myObjB.value << std::endl;
    
    std::cout << "address myObjB.value = " << &(myObjB.value) << std::endl; 
    std::cout << "address myObjB.A.value = " << &(((A*)&myObjB)->value) << std::endl; 
}
