#include <algorithm>
#include <string>
#include <iostream>
#include <cctype>
bool compare(const std::string::value_type& a, const std::string::value_type& b)
{ 
    std::string::value_type lower_a = tolower(a);
    std::string::value_type lower_b = tolower(b);
    if (lower_a == lower_b)
        return a < b;

    return lower_a < lower_b;
}

int main()
{
    std::string s("aAbB");
    std::sort(s.begin(), s.end(), compare);
    do {
        std::cout << s << std::endl;
    } while(std::next_permutation(s.begin(), s.end(), compare));
}