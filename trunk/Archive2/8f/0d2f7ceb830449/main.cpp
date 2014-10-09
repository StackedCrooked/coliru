#include <vector>
#include <stack>
#include <utility>
#include <iostream>

typedef std::vector<int> Block;

void iterate(std::stack<Block>& s)
{
    if (s.empty()) return;
    
    Block top{std::move(s.top())};
    s.pop();
    
    for (auto& i : top)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    
    iterate(s);    
    
    s.push(std::move(top));
}

int main()
{    
    std::stack<Block> blockStack;
    
    blockStack.push({1, 2, 3});
    blockStack.push({4, 5, 6});
    blockStack.push({7, 8, 9});    
    
    iterate(blockStack);
}
