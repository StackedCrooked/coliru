#include <memory>

int main()
{
    using T = char[3];
    char x[3];
    ::new((void*)x) T();
}