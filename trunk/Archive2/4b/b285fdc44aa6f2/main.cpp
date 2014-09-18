#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

typedef unordered_map<int,int> CacheTable;

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
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
std::cout << words << std::endl;


    
    CacheTable ct;
    ct[0] = 1;
    ct[1] = 1000;
    ct[2] = 2;
    int arr[] = {1,2,3};
    
    cout << ct[1,arr[0]]!=0;
}
