#include <string>
#include <algorithm>
#include <iostream>
#include <vector>
 
template<typename Container>
bool in_quote(const Container& cont, const std::string& s)
{
    return std::search(cont.begin(), cont.end(), s.begin(), s.end()) != cont.end();
}
 
int main()
{
    std::string str = "why waste time learning, when ignorance is instantaneous?";
    // str.find() can be used as well
    std::cout << std::boolalpha << in_quote(str, "learning") << '\n'
                                << in_quote(str, "lemming")  << '\n';
 
    std::vector<char> vec(str.begin(), str.end());
    std::cout << std::boolalpha << in_quote(vec, "learning") << '\n'
                                << in_quote(vec, "lemming")  << '\n';
}