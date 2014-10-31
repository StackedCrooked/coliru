#include <iostream>

template <typename T, typename F>
class Accessor
{
    friend F;
    
    template <typename... Args>
    Accessor(Args&&... args) : t{ args... } {}
    
    T t;
    
    Accessor& operator=(const T& rhs)
    {
        t = rhs;
        return *this;
    }

public:
    operator const T&() const { return t; }
};

class foo_t
{
public:
    Accessor<bool, foo_t> enabled_m;
    
    void set_this()
    {
        enabled_m = true; // works fine
    }
};

int main()
{
    foo_t foo;
    
    // foo.enabled_m = true; // doesn't work
    
    foo.set_this();
    std::cout << foo.enabled_m; // works fine    
}
