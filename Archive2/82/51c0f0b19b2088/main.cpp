#include <iostream>
#include <string>
#include <map>
#include <memory>

using namespace std;

struct Foo
{
    string name;
    
    Foo(string n) :
        name(n)
    {
    }
};

int main()
{
    auto foo1 = make_shared<Foo>("a");
    auto foo2 = make_shared<Foo>("b");
    
    map<string, pair<shared_ptr<Foo>, bool>> values;
    values.insert(make_pair("1", make_pair(foo1, true)));
    values.insert(make_pair("2", make_pair(foo2, false)));
    
    for(auto element : values)
    {
        cout << element.first << " " << element.second.first->name << " " << element.second.second << endl;
    }
}
