#include <iostream>
#include <algorithm>

bool areCharsUnique(std::string s) 
{
    std::sort(begin(s), end(s));
    return std::adjacent_find(begin(s), end(s)) == end(s);
}

int main() {
    std::string s1 = "hi there";
    std::string s2 = "hey man";
    std::cout << areCharsUnique(s1) << std::endl; //0
    std::cout << areCharsUnique(s2) << std::endl; //1
   return 0;   
}