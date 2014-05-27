#include <vector>
#include <string>
#include <iostream>

std::ostream & operator<<(std::ostream &os, std::vector<std::string> const& v); {
    for (auto const& s : v)
        os << s << ' ';
    return os;
}
 
int main(){
    
}