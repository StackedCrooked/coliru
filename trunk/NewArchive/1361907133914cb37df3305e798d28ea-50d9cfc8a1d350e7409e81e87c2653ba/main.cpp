#include <vector>

volatile int x = 0;

int main()
{        
    std::vector<int> vec;
    vec.push_back(x);
}