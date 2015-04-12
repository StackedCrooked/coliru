#include <vector>
#include <iostream>
#include <algorithm>
 
int main()
{
    std::vector<int> v{0,1,2,3,4,5}; 
    int k;
    int h = v.size();
    for (k=1; k<h;++k){
    // simple rotation to the left
    std::rotate(v.begin()+1, v.begin() + 2, v.end());
 
    std::cout << "simple rotate left  : ";
    for (int n: v)
        std::cout << n << ' ';
    std::cout << '\n';
    }
 
    // simple rotation to the right
    std::rotate(v.rbegin()+1, v.rbegin() + 2, v.rend());
 
    std::cout << "simple rotate right : ";
    for (int n: v)
        std::cout << n << ' ';
    std::cout << '\n';
 
}