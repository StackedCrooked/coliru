#include <algorithm>
int main()
{
    int a[] = { 1,2,3,4,5 };
    int *f(a), *l(a+5);

    int* where = std::find(f,l,3);
    return *where;
}
