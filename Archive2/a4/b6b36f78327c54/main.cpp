#include <iostream>
#include <utility>

int main()
{
    int i = []() -> int&&
        {
            int result = 1;
            return std::move(result);
        }();
        
    std::cout << "Move constructed from rvalue lambda: " << i << std::endl;
    return 0;
}
