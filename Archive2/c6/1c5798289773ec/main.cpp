#include <iostream>

struct Foo
{
    int bar;
    float baz;
};

int main()
{
    Foo arr[3] = { { 1, 2.0f }, { 2, 3.0f }, { 3, 4.0f } };
    
    Foo& fooA = arr[0];
    Foo* fooB = &arr[1];
    
    std::cout << fooA.bar << " " << fooB->baz << std::endl;
    
    return 0;
}