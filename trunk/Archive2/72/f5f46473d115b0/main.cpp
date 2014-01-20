#include <iostream>

template <typename type_t, typename func_t, func_t f>
struct T
{
    T() { f(); }
    
    type_t a;   /**< Irrelevant here, but left in to give your `type_t` something to do */
};

void foo() { std::cout << "A\n"; }
int  bar() { std::cout << "B\n"; return 0; }

int main()
{
    T<int, void(*)(), &foo> t1;
    T<int, int (*)(), &bar> t2;
}