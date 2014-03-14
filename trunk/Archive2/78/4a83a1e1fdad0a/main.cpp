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

int main()
{
    std::string str = "maria hernandez 1000 h3777 +1000 19:15:19\nrachel dominguez 100000 X8793 +100000 19:15:20\ncarlos yatch 20 g6386 +20 19:15:20\n\n\n\ncarlos Domingues 20 g3336 +20 19:15:20"; 
    std::cout << "Before:\n\n" << str << std::endl;
          
    size_t pos;
    while ((pos= str.find("\n\n", 0)) != std::string::npos)
    {
        str.erase(pos, 1);
    }
    std::cout << "\nAfter:\n\n" << str <<std::endl;
}
