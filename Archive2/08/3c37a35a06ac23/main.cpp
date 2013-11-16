#include <iostream>
#include <utility>

template<typename T>
struct wrapper
{
    wrapper() : t() {}
    explicit wrapper(T t) : t(t)  {}    
    
    wrapper(wrapper<T>&& rhs) : t(rhs.t)
    {
        rhs.t = T();
    }
    
    wrapper& operator=(wrapper<T>&& rhs)
    {
        t = rhs.t;
        rhs.t = T();
        return *this;
    }
    
    T t;
};


struct Array
{
    Array(int len) : data(new char[len]), length(len) { }
    Array(Array&&) = default;
    Array& operator=(Array&&) = default;
    ~Array()
    {
        delete [] data.t;
    }
    
    wrapper<char*> data;
    wrapper<int> length;
};


int main()
{
    Array a(1);
    Array b = std::move(a);
    a = std::move(b);
}
