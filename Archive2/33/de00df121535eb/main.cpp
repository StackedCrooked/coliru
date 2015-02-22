#include <unordered_set>
#include <string>
#include <iostream>

template <typename CharT>
bool isUnique(const std::basic_string<CharT>& s)
{
    if (s.size() <= 1)
        return true;
 
    std::unordered_set<CharT> charSeen;
    
    for (auto ch : s)
        if (!charSeen.insert(ch).second)
             return false;
    return true;
}

int main()
{
    std::cout << isUnique<wchar_t>(L"فعه") << '\n';
}