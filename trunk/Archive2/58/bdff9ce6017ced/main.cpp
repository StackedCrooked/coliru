#include <string>
#include <iostream>

void Test(const bool arg) 
{
    std::cout << "Wrong[" << arg << "]" << std::endl;
}
void Test(const std::initializer_list<std::string> arg)
{
    std::cout << "Right[" << arg.size() << "]" << std::endl;
}
    
int main (int /*argc*/, char * const /*argv*/[]) 
{
    Test({"false"});
    return 0;
}