#include <iostream>
#include <string>
#include <vector>

using namespace std;

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
   cout<<"\nHello Kartik";
}
