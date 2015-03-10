#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    int sum = 0;
    std::vector<int> ints = {1,2,3,4};
    std::for_each(ints.begin(), ints.end(), [&sum](int v){sum += v;});
    std::cout << sum << std::endl;
}
