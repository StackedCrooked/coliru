#include <iostream>
#include <algorithm>
#include <string>

std::string& ReplaceChars(std::string& s,
                          const std::string& sCharList,
                          const std::string& sReplacement)
{
    std::string::size_type pos = 0;
    while ((pos = s.find_first_of(sCharList,pos)) != std::string::npos)
    {
        s.replace(pos, 1, sReplacement);
        pos += sReplacement.length();
    }
    return s;
}

int main()
{
    std::string s = "DABBCDDEBA";
    std::cout << ReplaceChars(s, "BD", "xxx") << '\n';
    return 0;
}