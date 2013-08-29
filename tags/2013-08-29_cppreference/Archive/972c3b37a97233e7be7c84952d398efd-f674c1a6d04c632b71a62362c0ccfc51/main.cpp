#include <functional>
#include <iostream>
#include <utility>
using namespace std;

template<typename T>
class Property
{
    // Possible to avoid type erasure,
    // but would require enveloping class type in template params
    typedef function<T()> Get;
    typedef function<void(const T&)> Set;
    Get get;
    Set set;
public:
    Property(Get &&g, Set &&s)
        : get(move(g)), set(move(s))
    {}
    Property(const Property&)
    {} // must do nothing
    Property &operator=(const Property&)
    {} // must do nothing
    Property &operator=(const T &x)
    {
        set(x);
        return *this;
    }
    operator T() const
    {
        return get();
    }
};

#define UNBRACE(x) x
#define PROPERTY(type, name, getter_body, setter_body ) \
    Property<type> value{[this]() -> type { UNBRACE getter_body }, [this](const type &x){ UNBRACE setter_body } }

class Widget
{
    int value_;
public:
    PROPERTY
    (
        int, value,
        (cout << "getter" << endl; return value_;),
        (cout << "setter" << endl; value_ = x;)
    );
};

int main()
{
    Widget w;
    w.value = 5;
    cout << w.value << endl;
    w.value = 1;
    cout << w.value << endl;
}
