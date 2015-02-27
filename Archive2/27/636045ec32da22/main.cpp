#include <iostream>
#include <cassert>
#include <vector>
#include <string>
#include <algorithm>

int main()
{
    std::vector<int> v1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
 
    // Use one of stl algorithms to create one linear returning string stating if values are even or odd
    // than print this string on screen
    std::string s;
    std::for_each(v1.begin(), v1.end(), 
    [&](int num) mutable
    {        
        if (!(num%2))
        {
            s+="even ";
        }
        else
        {
             s+="odd ";
        }
    });
    std::cout<<s;
    assert("odd even odd even odd even odd even odd even " == s);
}