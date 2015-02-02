#include <cstddef>

int main()
{
    void *p1, *p2;
    return static_cast<char *>(p2) - static_cast<char *>(p1);
}