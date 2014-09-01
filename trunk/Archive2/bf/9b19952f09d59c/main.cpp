#include <iostream>

typedef int f;
namespace N{
    class A{
        friend void f(int);
    };
}