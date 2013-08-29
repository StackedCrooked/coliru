#include <map>

int main()
{
    std::map<const int, int> m1;
    std::map<int, int> m2;
    m1 = m2;
}