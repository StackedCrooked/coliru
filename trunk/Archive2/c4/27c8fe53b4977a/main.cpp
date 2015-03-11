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

const char* getEmptyName()
{
    return "";
}

const char* getNullName()
{
    return 0;
}


int main()
{
    std::string emptyName( getEmptyName() );
    std::string nullName( getNullName() );

    std::cout << "Check emptyName" << std::endl;
    if (emptyName.empty())
    {
        std::cout << "emptyName is empty" << std::endl;
    }
    else
    {
        std::cout << "emptyName is " << emptyName << std::endl;
    }

    std::cout << "Check nullName" << std::endl;
    if (nullName.empty())
    {
        std::cout << "nullName is empty" << std::endl;
    }
    else
    {
        std::cout << "nullName is " << nullName << std::endl;
    }
}
