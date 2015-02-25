#include <iostream>

struct Foo
{
    int arr[10];
    int size;
    int* ptr;
};

int main()
{
    Foo foo = {{1,2,3,4,5,6,7,8,9,10}, 10};
    Foo* fooey = &foo;
    
    for (fooey->ptr = fooey->arr; fooey->ptr < fooey->arr + fooey->size; ++fooey->ptr)
        std::cout << *(fooey->ptr) << ' ';
}
