#include <iostream>
#include <memory>
 
void foo(std::shared_ptr<int> i)
{
    (*i)++;
     std::cout << *i << std::endl;
}
 
int main()
{
    // auto sp = std::make_shared<int>(10);
    foo(std::shared_ptr<int>(new int(42)));
    //std::cout << *sp << std::endl;
}