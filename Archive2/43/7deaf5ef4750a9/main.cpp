#include <iostream>
#include <vector>
 
int main() 
{
    std::vector<int> v = {0, 1, 2, 3, 4, 5};
    int iarr[] = {10,20,30,40,50,60,70,80} 
    
    
    for (int i : {100,200,300,400,500,600}) // access by direct sequence of values
        std::cout << i << ' ';


     
    for (int &i : v) // access by reference (const allowed)
        std::cout << i << ' ';
 
    std::cout << '\n';
 
    for (auto i : v) // compiler uses type inference to determine the right type
        std::cout << i << ' ';
 
    std::cout << '\n';
 

    std::cout << '\n';
}