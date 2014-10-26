#include <iostream>
#include <vector>
#include <algorithm>

struct Y
{
    int i;
};

struct X
{
    int i;
    
    X(int i) : i(i) {}
    
    operator Y() const {return {i};}
};

int main()
{
    std::vector<X> argumentVector{1, 2, 3, 4, 5};
    
    std::vector<Y> argumentList;
    // […]
    argumentList.insert(argumentList.begin(), argumentVector.begin(), argumentVector.end());
    
    for (auto y : argumentList)
        std::cout << y.i << ", ";
}
