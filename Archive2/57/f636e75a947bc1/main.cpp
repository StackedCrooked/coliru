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

std::ostream& operator<<(ostream& os, Operations op)
{
    switch(op)
    {
        case Operations::add:
            return os << '+';
        case Operations::sub:
            return os << '-';
        case Operations::div:
            return os << '/';
        case Operations::mul:
            return os << '*';
        default: throw std::runtime_error("illegal Operation");
    }
}

template <class K, class V>
void displayMap ( map<K,V> const& m )
{
    for(auto const& kv : m ) {
        cout << kv.first 
             << " " 
             << kv.second
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
