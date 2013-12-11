#include <utility>
#include <stdio.h>

template<typename T> void print_type() { puts(__PRETTY_FUNCTION__); }


int main()
{   
    int a = 1;
    print_type<decltype(a)>();
    print_type<decltype((a))>();
}
