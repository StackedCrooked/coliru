#include <list>
using namespace std;

class DF
{
public:
    virtual void Append(list<int> list) = 0;
    list<int> GetFeature();
};

list<int> DF::GetFeature()
{
    list<int> list;
    Append(list);    // Error: identifier "Append" is undefined
    return list;
}

int main() {
    
}
