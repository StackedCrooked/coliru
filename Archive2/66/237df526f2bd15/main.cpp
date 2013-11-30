#include <iostream>
#include <string>
#include <vector>
#include <map>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

using namespace std;

int main()
{
    vector < string > test = { "Huhu", "Timey", "BlaBlubb", "Baba" };
    for( auto word = test.begin(); word < test.end(); word++ )
        cout << ( word - test.begin() ) << ": " << *word << "\n";
}
