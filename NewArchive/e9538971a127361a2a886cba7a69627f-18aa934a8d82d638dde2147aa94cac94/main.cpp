#include <iostream>
#include <vector>

int main()
{
    std::vector<int> v;
    for (auto i = 0; i != 10000000; ++i)
    {
        v.push_back(i);
    }
    return v.size();
}//aaaaaaaa