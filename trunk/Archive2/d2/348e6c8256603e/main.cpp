struct non_trivial
{
    int i;
    non_trivial()
    // default-initializes `i`
    {}
};

struct trivial
{
    int i;
    trivial() = default;
};

#include <iostream>

int main()
{
    auto n = non_trivial();
    auto t = trivial();
    
    std::cout << t.i << "\n";
    std::cout << n.i << "\n"; // UB
}