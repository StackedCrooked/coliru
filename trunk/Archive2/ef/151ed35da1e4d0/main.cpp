#include <vector>


int main()
{
    std::vector<std::vector<int> > res;
    res.emplace_back(std::initializer_list<int>{1,2});
}
