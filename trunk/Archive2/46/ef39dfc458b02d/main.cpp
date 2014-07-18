#include <functional>
#include <iostream>

using namespace std;

class foo
{
public:
    foo() : _myFunc( bind( &foo::testCall, this ) ){}
    virtual void testCall(){ cout << "foo" << endl; }
    void call(){ _myFunc(); }
private:
    function< void() > _myFunc;
};

class bar: public foo
{
public:
    virtual void testCall(){ cout << "bar" << endl; }
};

int main()
{
    bar test;
    test.call();
}