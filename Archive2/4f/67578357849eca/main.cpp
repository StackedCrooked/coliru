
#include <iostream>
#include <string>
#include <algorithm>

struct nospace_t {} nospace; 

std::string replace(std::string s, char old, nospace_t const &)
{
    s.erase(std::remove(begin(s), end(s), old),end(s));
    return s;
}

int main()
{
    char space = ' ';
    std::cout << replace("e m p h a s i s", space, nospace) << std::endl;
}
