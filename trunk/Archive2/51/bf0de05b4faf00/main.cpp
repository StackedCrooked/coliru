#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

int main()
{
    std::vector<const char*> Test;
    Test.push_back("F_S");
    Test.push_back("FC");
    Test.push_back("ID");
    Test.push_back("CD");
    Test.push_back("CT");
    Test.push_back("DS");
    Test.push_back("CR");
    Test.push_back("5K_2");
    Test.push_back("10K_5");
    Test.push_back("10K_1");
    Test.push_back("10K_2");
    Test.push_back("10K_3");
    Test.push_back("10K_4");
    Test.push_back("10K_5");
    
    std::vector<const char*> Unique_Data;
    
    for(auto const& s1 : Test) {
        if(std::find_if(Unique_Data.cbegin(), Unique_Data.cend(), 
            [&](const char *s2) { return std::strcmp(s1, s2) == 0; })
            == Unique_Data.cend()) {
            Unique_Data.push_back(s1);
        }
    }
    
    for(auto const& s : Unique_Data) {
        std::cout << s << '\n';
    }
}
