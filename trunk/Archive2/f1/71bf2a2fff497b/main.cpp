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
    Array() : data(), length() {}
    Array(int len) : data(new char[len]), length(len) { }
    
    Array(Array&& rhs) : Array()
    {
        swap(rhs);
    }
    
    Array& operator=(Array&& rhs)
    {
        swap(rhs); return *this;
    }
    
    void swap(Array& other) {
        std::swap(data, other.data);
        std::swap(length, other.length);
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
