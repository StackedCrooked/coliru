#include <vector>
#include <stack>
#include <utility>
#include <iostream>

typedef std::vector<int> Block;

struct MyStack : std::stack<Block>
{
    decltype(c.begin()) begin() { return c.begin(); }
    decltype(c.end()) end() { return c.end(); }
};

int main()
{    
    MyStack blockStack;
    
    blockStack.push({1, 2, 3});
    blockStack.push({4, 5, 6});
    blockStack.push({7, 8, 9});    
    
    for (auto& vec : blockStack)
    {
        for (auto& j : vec)
        {
            std::cout << j << " " ;
        }
        std::cout << std::endl;
    }
}
