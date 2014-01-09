#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <functional>

using namespace std;

class A
{
    public:
    int slot;
    string text;
};

typedef A* mytype;  
    
int main()
{
    A obj[5];
    int val[] = {1,4,3,2,0};

    map<mytype,string> mymap;  
    vector<mytype> v;

    for(int i = 4; i >= 0; --i)
    {
      obj[i].slot = val[i];
      mymap[&(obj[i])] = "";
    }
    
    for(auto it = mymap.begin(); it != mymap.end(); ++it)
    {
        cout << it->first->slot << "\n";
        v.push_back(it->first);
        
    }
    
    std::sort(v.begin(), v.end(), [](const mytype & left, const mytype & right) { return (left->slot < right->slot); } );

cout << "sortd\n";
    for(auto it = v.begin(); it!=v.end(); ++it)
     cout << (*it)->slot << "\n";
    
}
