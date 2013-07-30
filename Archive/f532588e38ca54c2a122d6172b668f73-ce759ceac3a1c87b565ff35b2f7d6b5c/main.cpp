#include <iostream>

struct S {
     int* p;    // a pointer
};

S x {new int{0}};
void f()
{
     S y(x);              // "copy" x

     *y.p = 1;             // change y; affects x
     *x.p = 2;             // change x; affects y
     delete y.p;           // affects x and y
     y.p = nullptr;
     std::cout << (y.p == x.p) << std::endl;
     y.p = new int{3};     // OK: change y; does not affect x
     std::cout << (y.p == x.p) << std::endl;
     *x.p = 4;             // oops: write to deallocated memory
}

int main()
{
    f();
    return 0;
}
