#include <iostream>

template<class...Args>
void printArgs(Args const&... args) {
    printArgs(args...);
}

template<class Arg>
void printArgs(Arg const& arg) {
    std::cout << arg;
}


int main(void)
{
    printArgs("hello", "world", "anthony");
}