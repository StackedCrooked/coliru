struct A
{
    int m;
    
    A* operator->()
    {
        return this;
    }
};

struct ptr_like
{
    A operator->() const
    {
        return {42};
    }
};

#include <iostream>

int main()
{
    auto p = ptr_like{};
    std::cout << p->m;
}