#include <iostream>
#include <cstring>
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

int main()
{
    char buffer[10];
    buffer[9] = '\0';
    strlen(buffer); 
}
