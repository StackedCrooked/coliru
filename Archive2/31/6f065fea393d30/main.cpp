#include <iostream>
#include <map>
#include <utility>

using namespace std;

int main()
{
    multimap<string, string> mymap;
    
    mymap.insert(make_pair("file1", "path1"));
    mymap.insert(make_pair("file1", "path2"));
    mymap.insert(make_pair("file1", "path3"));
    mymap.insert(make_pair("file2", "path1"));
    mymap.insert(make_pair("file3", "path2"));
    
    for(auto const& kv : mymap) {
        std::cout << kv.first << ": " << kv.second << '\n';
    }
}
