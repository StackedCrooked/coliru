#include <iostream>
#include <vector>

int main()
{
    struct { int a, b; } wow = { 1, 42 };
    std::vector<decltype(wow)> many_wows { wow, wow, wow };
    
    std::cout << many_wows.size();
}
