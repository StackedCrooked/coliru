#include <iostream>
#include <utility>


template<typename T>
T simple_move(T& src)
{
    static_assert(std::is_pod<T>::value, "");
    T dst = src;
    src = T();
    return dst;
}


struct Array
{
    Array(int len) : data(new char[len]), length(len) { }
    
    Array(Array&& rhs) :
        data(simple_move(rhs.data)),
        length(simple_move(rhs.length))
    {
    }
    
    Array& operator=(Array&& rhs)
    {
        data = simple_move(rhs.data);
        length = simple_move(rhs.length);
        return *this;
    }
    
    ~Array()
    {
        delete [] data;
    }
    
    char* data;
    int length;
};


int main()
{
    Array a(1);
    Array b = std::move(a);
    a = std::move(b);
}
