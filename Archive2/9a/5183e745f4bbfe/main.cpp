#include <iostream>

struct Tmp 
{
    Tmp(int ) { std::cout << "Constructor" << std::endl; }
    Tmp(const Tmp& ) { std::cout << "Copy Constructor" << std::endl; }
    Tmp(Tmp&& ) { std::cout << "Move Constructor" << std::endl; }
};

struct ConstructByValue
{
    ConstructByValue(Tmp t) : t(std::move(t)) { }
    Tmp t;
};

struct ConstructByCRef
{
    ConstructByCRef(const Tmp& t) : t(t) { }
    Tmp t;
};

int main()
{
    {
        ConstructByValue cbv(Tmp(1));
        std::cout << "------------------------" << std::endl;
        ConstructByCRef cbcr(Tmp(1));
        std::cout << "------------------------" << std::endl;
        (void)cbv;
        (void)cbcr;
    }
    {
        const Tmp t(1);
        std::cout << "------------------------" << std::endl;
        ConstructByValue cbv(t);
        std::cout << "------------------------" << std::endl;
        ConstructByCRef cbcr(t);
        std::cout << "------------------------" << std::endl;
        (void)cbv;
        (void)cbcr;
    }
}
