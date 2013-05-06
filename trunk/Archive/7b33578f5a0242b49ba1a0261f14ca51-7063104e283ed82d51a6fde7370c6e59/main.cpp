#include <iostream>
#include <vector>

struct bar {
    std::vector<int> nums;
};

int main()
{
    bar b;
    b.nums = {1, 2, 3};

    for(int b : b.nums)
        std::cout << b << std::endl;   
}
