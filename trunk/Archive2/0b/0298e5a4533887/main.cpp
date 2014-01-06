#include <cassert>

union T
{
    int x;
    const int y;
};

int main()
{
    T a{4};
    a.x = 5;
    a.y = 6;
}
