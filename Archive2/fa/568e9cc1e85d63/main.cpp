#include <iostream>
#include <cstdio>
#include <utility>
#include <vector>

    
void f(std::pair<std::vector<int>, int> s)
{
}
    
int main (int argc, char *argv [])
{
    f(std::make_pair<std::vector<int>>({1, 2, 3}, 4));
    
    return 0; 
}