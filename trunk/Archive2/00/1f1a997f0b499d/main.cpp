#include <iostream>

template<typename F, typename ...Args>
static auto wrap(F func, Args&&... args)
{
    return func(std::forward<Args>(args)...);
}

void f1(int, char, double)
{
    std::cout << "do nada1\n"; 
}

void f2(int, char='a', double=0.)
{
    std::cout << "do nada2\n"; 
}

int main()
{
    wrap(f1, 1, 'a', 2.); 
    wrap(f2, 1, 'a'); 
}
