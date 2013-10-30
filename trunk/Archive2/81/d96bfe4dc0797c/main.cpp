#include <functional>
#include <iostream>
#include <utility>

using namespace std;

struct Foo
{
    int bar(int x, float y, bool z)
    {
        cout << "bar: " << x << " " << y << " " << z << endl;
        return 0;
    }
};
int baz(int x, float y, bool z)
{
    cout << "baz: " << x << " " << y << " " << z << endl;
    return 0;
}

template<typename Obj, typename Result, typename ...Args>
struct Delegate
{
    Obj x;
    Result (Obj::*f)(Args...);
    
    template<typename ...Ts>
    Result operator()(Ts&&... args)
    {
        return (x.*f)(forward<Ts>(args)...);
    }
};

template<typename Obj, typename Result, typename ...Args>
auto make_delegate(const Obj &x, Result (Obj::*fun)(Args...)) -> Delegate<Obj, Result, Args...>
{
    Delegate<Obj, Result, Args...> result{x, fun};
    return result;
}

int main()
{
    Foo object;
    function<int(int,float,bool)> fun[] = { baz, make_delegate(object, &Foo::bar) };
    for(auto &x : fun)
        x(1, 1.0, 1);
}
