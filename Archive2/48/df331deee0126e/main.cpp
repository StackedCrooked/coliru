#include <vector>
#include <cassert>

int main()
{
    std::vector<int> v1{42, 1337};
    std::vector<int> v2(42, 1337);
    assert(v1 == v2);
}