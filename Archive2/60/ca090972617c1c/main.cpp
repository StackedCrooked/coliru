#include <unordered_map>
#include <string>
#include <iostream>

template <typename CharT>
bool isUnique(const std::basic_string<CharT>& s)
{
    if (s.size() <= 1)
        return true;
    
    std::unordered_map<wchar_t, bool> charSeen;
    for (int i = 0; i < s.size(); i++) {
        if (!charSeen[s[i]])
            charSeen[s[i]] = true;
        else
            return false;
    }
    return true;
}

int main()
{
    std::cout << isUnique(L"فعه") << '\n';
}