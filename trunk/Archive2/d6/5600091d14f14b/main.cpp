#include <vector>
#include <string>
#include <iostream>
 
template<typename T>
std::ostream& operator<<(std::ostream& s, const std::vector<T>& v) {
    s.put('[');
    char comma[3] = {'\0', ' ', '\0'};
    for (int i = 0; i < (int)v.size(); ++i) {
        s << comma << v[i];
        comma[0] = ',';
    }
    return s << ']';
}
 
int main() 
{
    // c++11 initializer list syntax:
    std::vector<std::string> words1(6, std::string(""));
    std::cout << "words1: " << words1 << '\n';
 
}