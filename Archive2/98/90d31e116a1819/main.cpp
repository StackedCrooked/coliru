#include <iostream>
#include <string>
#include <vector>
#include <map>

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


int main() {

    std::map<int, int> myMap;
    int key = myMap[1];
    myMap[2];
    myMap[1];
    int *key1 = myMap[3];

    cout << "items in map: " << myMap.size() << endl;
    cout << "count key 1: " << myMap[1] << endl;
    cout << "count key 2: " << key1 << endl;
    
}