#include <unordered_map>
#include <string>
#include <iostream>

template <typename CharT, typename AllocatorT>
bool isUnique(const std::basic_string<CharT, AllocatorT>& s)
{
    if (s.size() <= 1)
        return true;
    
    std::unordered_map<CharT, bool> charSeen;
    for (unsigned i = 0; i < s.size(); i++) {
        if (!charSeen[s[i]])
            charSeen[s[i]] = true;
        else
            return false;
    }
    return true;
}

int main()
{
    using namespace std::literals;
    std::cout << isUnique(L"فعه"s) << '\n';
}