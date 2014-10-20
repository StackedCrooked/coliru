#include <iostream>
#include <map>

typedef std::map<int, int> MappingTable;

int main()
{
    MappingTable runmap;
    MappingTable::iterator badIterator = runmap.rbegin().base();
    std::cout << "runmap.rbegin().base() == runmap.begin():" << (badIterator == runmap.begin() ? "yes" : "no") << std::endl;
    std::cout << "runmap.rbegin().base() == runmap.end():" << (badIterator == runmap.end() ? "yes" : "no") << std::endl;
}
