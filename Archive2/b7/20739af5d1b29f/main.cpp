#include <utility>
#include <string>
#include <iostream>
#include <map>

using namespace std;

int main()
{
    map<string, string> m { {"a","A"}, {"bla", "blubb"} };
    
    auto it = m.begin();
    std::advance(it, 5);
    std::cout << it->second;
}
