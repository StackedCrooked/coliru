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
template<> int globals_go_here<int>::o1;
//construct the second one
template<> dependent globals_go_here<int>::o2;

static int& o1=globals_go_here<int>::o1;
static dependent& o2=globals_go_here<int>::o2;

int main()
{
    //std::cout << globals_go_here<int>::o1; // linker error: undef ref
    globals_go_here<int>::o2.print();        // works fine
    // add a member variable to dependent and output it to get the linker error
    // again
}
