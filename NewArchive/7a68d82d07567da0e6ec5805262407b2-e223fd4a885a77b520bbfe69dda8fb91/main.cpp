#include <iostream>
#include <functional>

template<typename T>
class property
{
public:
    template<typename Get, typename Set>
    property(Get && g, Set && s) : _get{ std::forward<Get>(g) }, _set{ std::forward<Set>(s) }
    {
    }
    
    operator T() const
    {
        return _get(_t);
    }
    
    property<T> & operator=(const T & t)
    {
        _t = _set(t);
        return *this;
    }
    
private:
    std::function<int(int)> _get;
    std::function<int(int)> _set;
    T _t;
};

struct foo
{
    foo() : bar{ [this](int x) { ++counter; return x; }, [this](int x) { ++counter; return x; } }
    {
    }
    
    property<int> bar;
    int counter = 0;
};

int main()
{
    foo f;
    
    for (int i = 0; i < 1000; ++i)
    {
        f.bar = i;
        std::cout << f.bar << std::endl;
    }
    
    std::cout << f.counter << std::endl;
}
