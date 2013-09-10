#include <iostream>
template <typename> using lol = int; 

template<typename T> void f(lol<T> arg) {
    std::cout << arg;
}
int main()
{
    f(42);
}
