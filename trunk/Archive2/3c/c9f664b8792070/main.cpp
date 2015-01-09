#include <iostream>
#include <memory>
 
void foo(const std::shared_ptr<int>& i)
{
    (*i)++;
}
 
int main()
{
    try{
        auto sp = std::make_shared<int>(342524525245);
        foo(sp);
        std::cout << *sp << std::endl;
    }
    catch (...)
    {
        std:: cout << "Error" << std::endl;
    }

}