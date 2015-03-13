#include <iostream>


template <int I>
void f(int(&)[24 / (4 - I)]); // division by zero


template <int I>
void f(int(&)[24 / (4 + I)]);

int main()
{
        &f<4>;
}

