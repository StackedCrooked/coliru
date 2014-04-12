#include <vector>
#include <iostream>

int main()
{
    std::vector<std::vector<int>> numbers = {std::vector<int>{2, 3}, std::vector<int>{45, 3}};
    std::vector<int> tempVector3 = {9, 4};
    
    auto column = tempVector3.begin(); //better hope they have same elements as numbers
    for(auto &row : numbers)
    {
        row.push_back(*column++); //right to left so this works
    }
    
    for(const auto &row : numbers)
    {
        for(const int &column : row)
        {
            std::cout << column << ' ';
        }
        std::cout << std::endl;
    }
}