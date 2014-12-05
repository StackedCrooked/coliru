#include <iostream>
#include <string>
#include <algorithm>

using namespace std::literals::string_literals;

int main()
{
    for (auto pair : {std::make_pair("Hallo%"s, "Hallo World!"s),
                      std::make_pair("AA%"s, "B"s),
                      std::make_pair("A%"s, "Awef"s),
                      std::make_pair("\"C:/MyFolder%1\""s, "\"C:/MyFold\""s)})
    {
        auto& str1 = pair.first,
              str2 = pair.second;
        
        auto iters = std::mismatch( str1.begin(), str1.end(), str2.begin(), str2.end(), 
                                    [] (char lhs, char rhs) {return lhs != '%' && lhs == rhs;});
                                    
        if (iters.first  == str1.end()
         || iters.second == str2.end()
         || *iters.first == '%') // Success
            std::cout << str1 << " is %-equivalent with " << str2 << '\n';
    }
}
