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

template<typename T>
struct Deleter {
    void (*fn_ptr)(T *);  // the fn ptr that will delete the entities held by unique_ptr
    
    Deleter( void(*fn)(T *) ) : fn_ptr(fn) { }
    void operator() (Shell*p )  {  fn_ptr(p); }
};

template<typename T>
Deleter<T> delete_using( void(*fn)(T*) ) {
    return Deleter<T>(fn);
}

template <typename T>
unique_ptr<T, Deleter<T> >    make_unique_ptr( T *ptr, Deleter<T> del)
{
    unique_ptr<T, Deleter<T> >  p (ptr, Deleter<T>(del) );
    return p;
}

template <typename T>
unique_ptr<T, Deleter<T> >    make_unique_ptr( T *ptr, void (*del_fn)(T*) )
{
    unique_ptr<T, Deleter<T> >  p (ptr, Deleter<T>(del_fn) );
    return p;
}



int main()
{
    Deleter<Shell> deleter(freeShell);
    typedef unique_ptr<Shell, Deleter<Shell> > UniqueShellPtr;
    
    vector<UniqueShellPtr> vShells;
    for(int i=0; i<10; i++) {
        vShells.push_back( UniqueShellPtr(newShell(i), deleter) );
        vShells.push_back( UniqueShellPtr(newShell(i), Deleter<Shell>(freeShell) ) );
        vShells.push_back( UniqueShellPtr(newShell(i), delete_using(freeShell) ) );
        vShells.push_back( make_unique_ptr(newShell(i), delete_using(freeShell) ) );
        vShells.push_back( make_unique_ptr(newShell(i), freeShell ) );
    }

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