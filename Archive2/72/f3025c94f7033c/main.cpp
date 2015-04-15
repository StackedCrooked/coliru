#include <set>
#include <iostream>
int main()
{
    std::set<int> c = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    // erase all even numbers from c
    for(auto it = c.begin(); it != c.end(); )
        if(*it % 2 == 1)
        {
            it = c.erase(it);
            std::cout << *it << std::endl;
        }
            
        else
            ++it;
    for(int n : c)
        std::cout << n << ' ';
}