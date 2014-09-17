#include <iostream>
#include <memory>
 
void foo(const std::shared_ptr<int>& i)
{
    (*i)++;
}
 
int main()
{
    int i = 12;
    auto sp = std::make_shared<int>(i);
    foo(sp);
    std::cout << *sp << "\t" << i << std::endl;

}