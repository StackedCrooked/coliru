#include <iostream>
#include <functional>
#include <map>
#include <string>
#include <algorithm>

struct IBase : public std::unary_function <bool, int>
{
    virtual bool operator () (int arg) = 0;
    /*{
    std::cout << "Base:" << arg << std::endl;
    return true;
    }*/
};

struct CDerived : public IBase
{
    bool operator () (int arg)
    {
    std::cout << "Derived:" << arg << std::endl;
    return true;
    }
};

int main()
{
    std::vector<int> vec { 1,2,3,4,5 };
    
    IBase* pPred = new CDerived;
    std::for_each (begin (vec), end (vec), std::ref (*pPred));
    
    return 0;
}