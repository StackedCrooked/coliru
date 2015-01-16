#include <iostream>

int a;

void f()
{
    using ::a;
    using ::a;
}

int main(){ }