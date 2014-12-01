#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <iterator>
using namespace std;



int main()
{
    std::map<string,int> mapA;

    mapA["cat"] = 1;
    mapA["dog"] = 3;
    
    std::map<string,int> mapB;
    
    mapB["cat"] = 1;
    mapB["horse"] = 3;
    
    std::merge(
        std::begin(mapA),
        std::end(mapA),
        std::begin(mapB),
        std::end(mapB),
        std::inserter(mapA, std::begin(mapA))); 

    for(auto p : mapA)
      std::cout << p.first << " " << p.second << "\n";

}