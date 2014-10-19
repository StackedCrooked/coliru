#include <map>

typedef std::map<int, int> MappingTable;

int main()
{
    MappingTable runmap;
    MappingTable::iterator last = runmap.empty() ? runmap.end() : (--runmap.end());
}
