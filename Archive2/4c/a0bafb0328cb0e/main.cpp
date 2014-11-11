#include <cstdlib>

int main()
{
    struct T {};
    T a;
    T b;
    static_assert(&a != &b);
    return EXIT_SUCCESS;
}
