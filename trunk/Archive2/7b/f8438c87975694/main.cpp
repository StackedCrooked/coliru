#include <vector>
#include <type_traits>
#include <iostream>

using namespace std;

template<class T, class U>
struct Iterable
{
    T _begin;
    U _end;

    Iterable(T begin, U end)
    : _begin(begin), _end(end)
    {}

    T begin()
    {
        return _begin;
    }

    U end()
    {
        return _end;
    }
};

template<class T, class U>
Iterable<T,U> make_iterable(T t, U u)
{
    return Iterable<T,U>(t, u);
}

struct MyClass 
{
    std::vector<int> _ints;
    std::vector<std::string> _strings;

    auto allInts() -> decltype(make_iterable(_ints.begin(), _ints.end()))
    {
        return make_iterable(_ints.begin(), _ints.end());
    }

    auto allStrings() -> decltype(make_iterable(_strings.begin(), _strings.end()))
    {
        return make_iterable(_strings.begin(), _strings.end());
    }
};

int main()
{
    MyClass foo;
    foo._ints = {1,2,3};
    foo._strings = {"a","b","c"};

    for (auto i : foo.allInts())
    {
        cout << i << endl;
    }

    for (auto i : foo.allStrings())
    {
        cout << i << endl;
    }
}