#include <iostream>
#include <map>

typedef std::map<int, int> MappingTable;

int main()
{
    MappingTable runmap;
    MappingTable::iterator it = runmap.rbegin().base();
    std::cout << "runmap.rbegin().base() == runmap.begin():" << (it == runmap.begin() ? "yes" : "no") << std::endl;
    std::cout << "runmap.rbegin().base() == runmap.end():" << (it == runmap.end() ? "yes" : "no") << std::endl;
    
    runmap.emplace(1, 2);
    it = runmap.rbegin().base();
    std::cout << "runmap.rbegin().base() == runmap.begin():" << (it == runmap.begin() ? "yes" : "no") << std::endl;
    std::cout << "runmap.rbegin().base() == runmap.end():" << (it == runmap.end() ? "yes" : "no") << std::endl;
    
}
