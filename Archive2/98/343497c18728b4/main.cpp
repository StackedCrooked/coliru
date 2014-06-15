#include <iostream>
#include <map>
#include <string>
#include <type_traits>

using namespace std;

enum class Operations
{
    add,
    sub,
    div,
    mul
};

template <class K, class V>
void displayMap ( map<K,V> &m )
{
    typename map<K,V>::iterator inx = m.begin();
    for ( ;inx != m.end(); ++inx )
    {
        cout << inx-> first 
             << " " 
             << static_cast<typename std::underlying_type<V>::type>(inx->second) 
             << endl;
    }
}


int main ( )
{

    static map<string, Operations> myMap;

    myMap.insert( make_pair ("add", Operations::add) );
    myMap.insert( make_pair ("sub", Operations::sub) );
    myMap.insert( make_pair ("div", Operations::div) );
    myMap.insert( make_pair ("mul", Operations::mul) );

    displayMap (myMap);

    return 0;
}
