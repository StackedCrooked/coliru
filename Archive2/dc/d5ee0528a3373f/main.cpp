#include <iostream>

template<class Fun, class... Args>
void CallFunction(Fun fun, Args&&... args)
{
    fun(std::forward<Args>(args)...);
}

void fn(int a1, bool a2, char const* a3)
{
    std::cout << a1 << a2 << a3;    
}

int main() 
{
    CallFunction(fn, 10, true, "Hello");
}
