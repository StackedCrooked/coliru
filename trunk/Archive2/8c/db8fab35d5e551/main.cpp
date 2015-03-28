#include <vector>
#include <iostream>
#include <algorithm>

//Functon we'll use to compare
bool compare(int i, int j) { return (i < j); }

int main()
{
    //Let's create a dummy list
    int int_list[] = {1,3,6,2,8,10,32,22};
    
    //Create a vector from the dummy list
    std::vector<int> one (int_list, int_list + 8);
    
    //Use std::sort and iterators to use the compare() to sort
    std::sort(one.begin(), one.end(), compare);
    
    //Let's create a second vector that is the reverse of one.
    std::vector<int> two;
    
    //Use reverse iterator to go from back to front.
    for(auto rev_it = one.rbegin(); rev_it != one.rend(); ++rev_it)
    {
        two.push_back(*rev_it);    
    }
    
    //Print out the two vectors
    std::cout << "Vector one: ";
    for(auto it = one.begin(); it != one.end(); ++it)
        std::cout << *it << " ";
    std::cout << "\n";
    
    std::cout << "Vector two: ";
    for(auto it = two.begin(); it != two.end(); ++it)
        std::cout << *it << " ";
    std::cout << "\n";
}