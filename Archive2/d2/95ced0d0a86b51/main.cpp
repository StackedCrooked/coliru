/***************************************************/
#include <boost/function.hpp>
#include <boost/bind.hpp>

template<typename Base, typename Func>
struct Wrapper;

template<typename Base, typename Result, typename ...Args>
struct Wrapper<Base, Result(Args...)>: Base
{
    boost::function<Result(Args...)> callback;

    Result operator()(Args... args)
    {
        return callback(args...);
    }
};
/***************************************************/

#include <iostream>
using namespace std;

struct Base {};

struct Derived: Base
{
    void call(int x)
	{
		cout << x << endl;
	}
};

int main()
{
    Derived x;
    Wrapper<Base, void()> w;
    w.callback = boost::bind(&Derived::call, &x, 11);

    Base *b = &w;
    void (Base::*m)() = static_cast<void (Base::*)()>(&decltype(w)::operator());
    (b->*m)();
}
