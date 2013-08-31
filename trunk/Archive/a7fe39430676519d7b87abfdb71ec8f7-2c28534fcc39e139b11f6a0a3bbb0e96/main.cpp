#include <boost/utility/in_place_factory.hpp>
#include <boost/optional.hpp>
#include <iostream>
#include <utility>

using namespace boost;
using namespace std;

template<typename T, typename Factory>
class Lazy
{
    mutable optional<T> x;
    Factory f;
    T *constructed() const
    {
        if(!x) x = f;
        return &*x;
    }
public:
    Lazy(Factory &&f) : f(f) {}

    T *operator->()
    {
        return constructed();
    }
    const T *operator->() const
    {
        return constructed();
    }
};

template<typename T, typename ...Args>
auto make_lazy(Args&&... args) -> Lazy<T, decltype(in_place(forward<Args>(args)...))>
{
    return {in_place(forward<Args>(args)...)};
}

/*****************************************************/

struct Widget
{
    Widget(int x)
    {
        cout << "Widget(" << x << ")" << endl;
    }
    void foo()
    {
        cout << "Widget::foo()" << endl;
    }
};

int main()
{
    auto &&x = make_lazy<Widget>(11);
    cout << "after make_lazy" << endl;
    x->foo();
}