#include <iostream>
#include <cstring>

template<typename T, size_t n>
class string_test;

template<typename T, size_t n>
string_test<T, n> make_string(const T (&str)[n])
{
    return string_test<T, n>(str);
}

template<typename T, size_t n>
class string_test
{
    using Type = T;
    // Don't count NUL byte
    size_t _size = n - 1;
    char _buffer[n];
public:
    string_test()
    {
    }
    
    string_test(const char* str)
    {
        strcpy(_buffer, str);
    }
    
    ~string_test()
    {
    }
    
    size_t size() const
    {
        return _size;
    }
    
    const char* c_str() const
    {
        return _buffer;
    }
    
    auto begin()
    {
        return _buffer;
    }
    
    auto end()
    {
        return _buffer + _size;
    }

    template <typename U, size_t m>
    string_test<T, m + n> operator+(const string_test<U, m>& rhs)
    {
        char tmp[n + m];
        strcpy(tmp, _buffer);
        strcat(tmp, rhs._buffer);
        return make_string(tmp);
    }
};

int main()
{
    auto s = make_string("hello, world!");
    auto b = s;
    auto c(s);
    auto d = b + c;
    auto e = make_string("hello,");
    auto f = make_string(" world!");
    f = f + e;
    std::cout << f.c_str();
    return 0;
}
