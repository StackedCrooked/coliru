#include <vector>

int main()
{
    std::vector<int> v;
    v.insert(v.rbegin().base(), 0);
    return v.size();
}