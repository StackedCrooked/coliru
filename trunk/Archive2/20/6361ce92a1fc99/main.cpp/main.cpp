struct just_some_type
{
    int m;
    
    int transform() { return m; }
};

struct intermediate_helper
{
    just_some_type member;
    
    just_some_type* operator->() { return &member; }
};

struct ptr_like
{
    just_some_type operator*()
    { return {42}; }
    
    intermediate_helper operator->()
    { return {{42}}; }
};


#include <iostream>

int main()
{
    auto p = ptr_like{};
    std::cout << (*p).transform() << "\n";
    std::cout << p->transform() << "\n";
}