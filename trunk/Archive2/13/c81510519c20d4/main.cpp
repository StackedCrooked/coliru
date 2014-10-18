#include <iostream>

struct S
{
    int* i;
};

int main() {
    std::cout << sizeof(S) << std::endl;
}