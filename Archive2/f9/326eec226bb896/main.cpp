#include <iostream>
#include <memory>

void f (std::shared_ptr<int> ptr)
{
    ptr = std::make_shared<int>(5);  
}

void f (std::shared_ptr<int>* ptr)
{
    (*ptr) = std::make_shared<int>(5);  
}


int main()
{
    auto in = std::make_shared<int>(0);
    f(&in);
    std::cout << *in;
}
