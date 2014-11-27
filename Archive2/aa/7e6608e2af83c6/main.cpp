#include <list>
#include <iostream>
 
int main()
{
    std::list<int> l = { 1,100,2,3,10,1,11,-1,12 };
 
    l.remove(1); // remove both elements equal to 1
    l.remove_if([](int n){ return n > 0; }); // remove all elements greater than 10
 
    for (int n : l) {
        std::cout << n << ' '; 
    }
    std::cout << '\n';
}