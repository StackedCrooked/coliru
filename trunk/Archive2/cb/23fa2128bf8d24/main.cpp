#include <vector>
#include <iostream>
#include <algorithm>

bool compare(int i, int j) { return (i < j); }

int main()
{
    int int_list[] = {1,3,6,2,8,10,32,22};
    
    std::vector<int> one (int_list, int_list + 8);
    
    std::sort(one.begin(), one.end(), compare);
    
    //Let's create a second vector that is the reverse of one.
    std::vector<int> two;
    
    for(auto rev_it = one.rbegin(); rev_it != one.rend(); ++rev_it)
    {
        two.push_back(*rev_it);    
    }
    
    std::cout << "Vector one: ";
    for(auto it = one.begin(); it != one.end(); ++it)
        std::cout << *it << " ";
    std::cout << "\n";
    
    std::cout << "Vector two: ";
    for(auto it = two.begin(); it != two.end(); ++it)
        std::cout << *it << " ";
    std::cout << "\n";
    
    
    
}