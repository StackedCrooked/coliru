#include <iostream>

template<class ...Ts>
void auto foo(Ts... Vs)
{
    std::cout << (unsigned)Vs...;
}

int main() {
   foo(3, 5u, 6.123);
}