#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

struct Baseclass
{
    virtual ~Baseclass() {}
};

class someclass //that stores the references
{
public:

    // ..........

    template <typename T>
    T* getComponent(string name) 
    // headers and cpp files are actually seperated 
    {
        auto itr = _map.find(name);
        if (itr == _map.end())
            return 0;
        return dynamic_cast<T*>(itr->second);
    }

private:
    unordered_map<string, Baseclass*> _map;
};

struct DerivedFromBase : Baseclass {};

int main() {
    someclass derp;
    cout << "get = " << derp.getComponent<DerivedFromBase>("foo") << endl;
}
