#include <iostream>
#include <string>
#include <map>

using namespace std;

int main()
{
    string name = "John";
    int count = 200;
    map<string, int> store;
    map<string, int>::iterator it;

    it = store.find(name);

    if (it != store.end())
    {
        it->second += count;
    }
    else
    {
        store.insert(make_pair(name, count));
        cout << "ADDING NEW VALUE" << endl;
    }
}
