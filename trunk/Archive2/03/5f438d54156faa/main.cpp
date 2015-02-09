#include <iostream>
#include <string>
#include <vector>
#include <queue>

int main()
{
    std::vector<int> container;
    std::priority_queue<int, std::vector<int>&> priotityq( container );
    
    priorityq.push( 50 );
    for (auto& item : container ) {
        std::cout << item <<  << " ";
    }
    std::cout << std::endl;
}
