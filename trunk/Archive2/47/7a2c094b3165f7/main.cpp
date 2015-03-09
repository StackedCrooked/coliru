#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <map>
 
int main()
{
    std::multimap<int, float> mm;
    mm.insert(std::make_pair(1, 4.12));
    return 0;
}