#include <memory>
#include <iostream>
#include <string.h>

int test()
{
    return 42;
}

void close(int*)
{
    std::cout << "close.\n";
}

int main() {
    int i = test();
    std::unique_ptr<int, void(*)(int*)>
        t_copy { &i, close};
}