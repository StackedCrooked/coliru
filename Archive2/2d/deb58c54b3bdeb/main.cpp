#include <memory>
#include <iostream>


int main()
{
    std::unique_ptr<int> arf;
    std::cout << std::boolalpha << ( arf == nullptr ) << std::endl;
}
