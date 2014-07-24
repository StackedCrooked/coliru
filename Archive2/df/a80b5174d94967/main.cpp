#include <iostream>
#include <memory>
 
void foo(const std::shared_ptr<int>& i)
{
    (*i)++;
}
 
int main()
{
    auto sp = std::make_shared<int>(12);
    foo(sp);
    std::cout << *sp << std::endl;
}