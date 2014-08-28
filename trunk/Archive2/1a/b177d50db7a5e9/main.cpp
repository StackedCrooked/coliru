#include <algorithm>
#include <string>
#include <iostream>
 
int main()
{
    std::int s = "123";
    std::sort(s.begin(), s.end());
    do {
        std::cout << s << '\n';
    } while(std::next_permutation(s.begin(), s.end()));
}