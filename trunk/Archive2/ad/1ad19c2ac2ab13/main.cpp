#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

std::size_t getUniqueCharacters(std::string s)
{
    std::sort(std::begin(s), std::end(s));
    s.erase(std::unique(std::begin(s), std::end(s)), std::end(s));
    return s.size();
}

int main(){
    std::string s1 = "sparnus";
    std::string s2 = "sapnus";
    
    getUniqueCharacters(s1);
    std::cout << getUniqueCharacters(s1) << '\n';
    std::cout << getUniqueCharacters(s2) << '\n';
    return 0;
}