#include <map>
#include <vector>
#include <list>
#include <memory>
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
};

Shell *newShell(int id)
{
    Shell *p = (Shell*)malloc(sizeof(Shell));
    p->id = id;
    
    cout << "creating shell " << id << endl;
    
    return p;
}

void freeShell( Shell *p )
{
    cout << "freeing Shell " << p->id << endl;
    
    free(p);
}

struct ShellDeleter {
    void operator() (Shell*p )  {  freeShell(p); }
};

int main()
{
    typedef unique_ptr<Shell, ShellDeleter> UniqueShellPtr;
    
    vector<UniqueShellPtr> vShells;
    for(int i=0; i<10; i++)
        vShells.push_back( UniqueShellPtr(newShell(i)) );

//    vector<UniqueShellPtr>::iterator it;
//    for( it = vShells.begin(); it != vShells.end(); ++it ) 
//    {
//        cout << "accessing shell " << (*it)->id << " in vector" << endl;
//    }
    
    for( size_t i = 0; i < vShells.size(); ++i ) 
    {
        cout << "accessing shell " << vShells[i]->id << " in vector" << endl;
    }
}