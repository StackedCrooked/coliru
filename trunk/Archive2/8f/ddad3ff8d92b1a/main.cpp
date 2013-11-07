#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <iostream>

using namespace std;
using namespace boost;

struct Base {};

struct Derived: Base
{
    void call(int x)
	{
		cout << x << endl;
	}
};

struct Wrapper: Base
{
    function<void()> callback;
    void operator()()
    {
        callback();
    }
};

int main()
{
    Derived x;
    Wrapper w;
    w.callback = boost::bind(&Derived::call, &x, 11);

    Base *b = &w;
    void (Base::*m)() = static_cast<void (Base::*)()>(&Wrapper::operator());
    (b->*m)();
}
