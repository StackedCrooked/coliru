/*
现在有一棵二叉树，树上的节点有一个0-9的值。从根到叶子节点的路径上构成一个整数，求这些整数的和
       1
      / \
     2   3

就是12 + 13 = 25
*/

#include <iostream>
#include <string>
#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
}
