#include <iostream>
#include <utility>
#include <ostream>
#include <mutex>

using namespace std;

typedef int Money;

struct Account
{
    Money money = 1000;
    // ...
};

template<typename T>
T &lvalue(T &&t)
{
    return t;
}

template<typename T>
class monitor
{
    mutable mutex m;
    mutable T t;
public:
    template<typename F>
    auto operator()(F f) const -> decltype(f(t))
    {
        return lock_guard<mutex>(m),
               f(t);
    }
    template<typename F,typename ...Ts> friend
    auto transaction(F f,const monitor<Ts>& ...ms) ->
        decltype(f(ms.t ...))
    {
        return lock(lvalue(unique_lock<mutex>(ms.m,defer_lock))...),
        f(ms.t ...);
    }
};

int main()
{
    monitor<Account> m[2];

    transaction([](Account &x,Account &y)
    {
        x.money-=100;
        y.money+=100;
    },m[0],m[1]);

    for(auto &&t : m)
        cout << t([](Account &x){return x.money;}) << endl;
}