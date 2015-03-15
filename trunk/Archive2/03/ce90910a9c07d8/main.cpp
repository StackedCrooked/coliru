#include <iostream>
#include <string>
#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

int hashStringRecurse(std::string& str)
{
    char c = *(str.begin());
    str.erase(str.begin());
    return c * hashStringRecurse(str);
}

int hashString(std::string str)
{
    // This is kinda hacky, but I need this wrapper so that I'm only changing
    // a copy of str
    return hashStringRecurse(str);
}

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
    
    std::string key = "Hello";
    int hash = hashString(key);
    
    std::cout << "Hash of " << key << " = " << hash;
}
