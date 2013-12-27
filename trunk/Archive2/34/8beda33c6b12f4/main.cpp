#include <cassert>

union T
{
    int x;
    const int y;
    const int z;
};

int main()
{
    T a{4};
    a.x = 5;
    a.y = 6;
    a.z = 7;
}
