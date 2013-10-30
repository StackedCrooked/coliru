#include <map>
#include <vector>
#include <list>
#include <unordered_map>
#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <cassert>

using namespace std;
using namespace std::placeholders;

struct Shell
{
    int id;
    Shell (int ID) : id(ID) { }
    bool operator< (const Shell &other) const
    {
        return id < other.id;
    }
};




int main()
{

    vector<Shell> shells = { 5, 2, 3, 1, 4 };
    
    std::sort(shells.begin(), shells.end(), std::less<Shell>() );
    
    for(Shell s:shells)
        cout << s.id << " ";
    cout << endl;

}