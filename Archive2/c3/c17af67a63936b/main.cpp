#include <iostream>
#include <queue>
#include <vector>

struct foo
{
    foo(int v) {}
};

auto Less = [](foo const& a, foo const& b) -> bool
{
    return true; // do whatever comparison you need 
};

int main()
{
    using my_priority_queue = std::priority_queue<foo, std::vector<foo>, decltype(Less)>;
    
    my_priority_queue data(Less); // pass a copy of the comparator 
}
