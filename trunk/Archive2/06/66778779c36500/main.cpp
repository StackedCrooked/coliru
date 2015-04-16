#include <iostream>
#include <ostream>
#include <vector>

using namespace std;

struct Item
{
    void m1(int i)
    {
        cout << "m1(" << i << ")" << endl;
    }
};
struct DerivedItem : Item
{
    void m2(int i)
    {
        cout << "m2(" << i << ")" << endl;
    }
};

template<typename Derived>
struct IBase
{
    void m1(int i)
    {
        for(auto &&z : static_cast<Derived*>(this)->x)
        {
            z.m1(i);
        }
    }
};
template<typename Derived>
struct IDerivedBase: IBase<Derived>
{
    void m2(int i)
    {
        for(auto &&z : static_cast<Derived*>(this)->x)
        {
            z.m2(i);
        }
    }
};

struct Base : IBase<Base>
{
    vector<Item> x;
};
struct DerivedBase : IDerivedBase<DerivedBase>
{
    vector<DerivedItem> x;
};

int main()
{
    Base b;
    b.x.resize(3);
    DerivedBase d;
    d.x.resize(1);

    b.m1(11);
    d.m1(22);
    d.m2(33);
}