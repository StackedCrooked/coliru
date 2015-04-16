#include <boost/move/utility.hpp>
#include <iostream>
#include <ostream>

using namespace std;

class Movable
{
    BOOST_MOVABLE_BUT_NOT_COPYABLE(Movable)
    bool own_resource;
public:
    Movable()
        : own_resource(true)
    {}
    ~Movable()
    {
        cout << (own_resource ? "owner" : "empty") << endl;
    }
    Movable(BOOST_RV_REF(Movable) x)
        : own_resource(x.own_resource)
    {
        x.own_resource = false;
    }
    Movable& operator=(BOOST_RV_REF(Movable) x)
    {
        own_resource = x.own_resource;
        x.own_resource = false;
        return *this;
    }
};

Movable make()
{
    return Movable();
}

int main()
{
    Movable m = make();
}
