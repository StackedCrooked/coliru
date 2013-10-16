#include <set>
#include <iostream>
#include <string>
#include <algorithm>
#include <cassert>

using namespace std;

int main()
{
    string str("Hello");
    str.append("World");
    
    size_t pos = str.find("Wo");
    
    std::cout << pos;
}