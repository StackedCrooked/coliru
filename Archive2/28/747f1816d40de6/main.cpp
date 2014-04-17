#include <map>

int main()
{
    std::map<int, int> m1;
    std::map<decltype(m1)::const_iterator, int> m2;
    auto it = m1.cend();
    m2.emplace(it, 3);
}