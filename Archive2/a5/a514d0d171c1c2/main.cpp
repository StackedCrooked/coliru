#include <iostream>
#include <vector>

int main()
{
    auto somelist = std::vector<int>{1,2,3,4,5,6,6,7,8,9,6};
    
    for (auto first = begin(somelist), last = end(somelist); true;) {
        std::cout << *first++;     
        if (first == last) break;
        std::cout << ", ";
    }
}