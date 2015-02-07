#include <iostream>
#include <memory>

using my_ptr = std::unique_ptr<int, decltype(&free)>;

int main()
{
    std::cout << "sizeof int* " << sizeof(int*) << std::endl;
    std::cout << "sizeof std::unique_ptr<int> " << sizeof(std::unique_ptr<int>) << std::endl;
    std::cout << "sizeof std::unique_ptr<int[]> " << sizeof(std::unique_ptr<int[]>) << std::endl;
    std::cout << "sizeof std::unique_ptr<int, decltype(&free)> " << sizeof(std::unique_ptr<int, decltype(&free)>) << std::endl;
}
