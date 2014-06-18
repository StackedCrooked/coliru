#include <iostream>
#include <string>

class A
{
    public: 
    
    virtual std::string ici() = 0;
    void foo() { std::cout << ici() << std::endl; }
    
    void banane() { foo(); }
};

class B : public A
{
    public: 
    std::string ici() { return "ici"; };
    static void foo() { std::cout << "static foo" << std::endl; }
};

int main()
{
    B b;
    b.banane();
    
    return 0;
}