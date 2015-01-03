#include <iostream>

int a[][2] = {{1, 4}, {2, 6}};
int b[][3] = a;

struct A
{
    void foo() const &{ }
};

int main(){ }