#include <iostream>
#include <memory>

int main()
{
    std::cout << "sizeof int* " << sizeof(int*) << std::endl;
    std::cout << "sizeof std::unique_ptr<int> " << sizeof(std::unique_ptr<int>) << std::endl;
}
