#include <new>

struct item {};

int main()
{
    alignas(item) char data[sizeof(item)];
    new (data) item();
}