#include <memory> 
#include <iostream> 
 
void fun(std::shared_ptr<int> sp)
{
    std::cout << "fun: sp.use_count() == " << sp.use_count() << std::endl; 
}
 
int main() 
{ 
    std::shared_ptr<int> sp1 {std::make_shared<int>(5)};
    std::cout << "sp1.use_count() == " << sp1.use_count() << std::endl; 
 
    fun(sp1);
}