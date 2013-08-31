#include <vector>

volatile int x = 0;

int main()
{        
    std::vector<int> vec;
    vec.emplace_back(x);
    vec.push_back(x);
}