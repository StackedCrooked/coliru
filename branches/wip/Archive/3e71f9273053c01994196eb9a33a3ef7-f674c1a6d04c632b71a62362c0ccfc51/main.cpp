#include <vector>


int main()
{
    std::vector<int> v;
    auto it = v.begin();
    decltype(it)::value_type val;
}