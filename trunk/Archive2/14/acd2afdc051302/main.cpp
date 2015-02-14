#include <iostream>
#include <map>


typedef struct {
    int bar;
    int baz;
} Foo;

using namespace std;

int main()
{
    Foo dummy = {5, 8};
    map<unsigned int, Foo> myMap;
    myMap[0] = dummy;
    for (auto iter : myMap){
        cout << iter.first << ":" << iter.second.bar << ":" << iter.second.baz << endl;
    }
}
