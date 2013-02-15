#include <type_traits>

struct POD
{
    operator int() const { return n; }
    int n;
};


int main()
{
    POD p = POD();
    static_assert(std::is_pod<POD>::value, "");
    return p;
}