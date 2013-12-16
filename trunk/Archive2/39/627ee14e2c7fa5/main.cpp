#include <new>

int main()
{
    void* p = operator new(sizeof(int));
    new(p) [[MyObject]] int(17);
}