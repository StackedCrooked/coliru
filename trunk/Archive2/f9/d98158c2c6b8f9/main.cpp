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
    argumentList.reserve(argumentVector.size());
    std::copy( std::begin(argumentVector), std::end(argumentVector), std::back_inserter(argumentList) );
    
    for (auto y : argumentList)
        std::cout << y.i << ", ";
}
