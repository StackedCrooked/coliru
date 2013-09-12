#include <iostream>

struct independent
{};
struct dependent 
{
    void print() { std::cout << "meow"; }
};

template<class T>
struct globals_go_here{
    static int o1;
    static dependent o2;
};
//construct the first one
template <class T> int globals_go_here<T>::o1;
//construct the second one
template <class T> dependent globals_go_here<T>::o2;

static int& o1=globals_go_here<int>::o1;
static dependent& o2=globals_go_here<int>::o2;

int main()
{
    std::cout << globals_go_here<int>::o1; // linker error: undef ref
}
