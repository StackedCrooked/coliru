#include <iostream>
#include <vector>

int main()
{
    auto somelist = std::vector<int>{1,2,3,4,5,6,6,7,8,9,6};
    
    auto first = begin(somelist), last = end(somelist);
    if (first != last) {                // initial check
        while (true) {
            std::cout << *first++;     
            if (first == last) break;   // check in the middle
            std::cout << ", ";
        }
    }
}