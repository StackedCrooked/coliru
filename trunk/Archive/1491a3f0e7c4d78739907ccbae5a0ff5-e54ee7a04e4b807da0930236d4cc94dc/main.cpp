#include <vector>
#include <string>
#include <iostream>

struct Data
{
    Data(const std::string& name, int x):
        m_Name(name),
        m_X(x)
    {}

    std::string m_Name;
    int m_X;
};

std::vector<Data> datas = 
{
    { "one"  , 1},
    { "two"  , 2},
    { "three", 3},
};

int main()
{
    for(auto const& i: datas)
        std::cout << i.m_Name << " "  << i.m_X << "\n";
}