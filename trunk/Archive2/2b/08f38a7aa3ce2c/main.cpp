#include <vector>
#include <cstring>
#include <algorithm>
#include <iostream>
 
int main() 
{
    std::vector<const char*> cats {"Heathcliff", "Snagglepuss", "Hobbes", "Garfield"};
    std::sort(cats.begin(), cats.end(), [](const char *strA, const char *strB) {
        return std::strcmp(strA, strB) < 0;
    }); 
 
    for (const char *cat : cats) {
        std::cout << cat << '\n';
    }
}