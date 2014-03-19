#include <iostream>
#include <iterator>
#include <vector>

int main()
{
    std::vector<int> v{};
    auto inserter = std::back_inserter(v);
    for(int i=0; i<100; ++i)
    {
      inserter = i;
    }

    for(const auto item : v)
    {
      std::cout << item << '\n';
    }
}