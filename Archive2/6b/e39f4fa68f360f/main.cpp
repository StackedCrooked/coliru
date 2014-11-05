//Title of this code
#include <iostream>
#include <cmath>

template <typename T> struct CSizex {
};

template <typename T> struct CPointx {
};

struct Logger
{
    template <typename T> Logger& operator<<(const CSizex<T>& size) {return *this;}
    template <typename T> Logger& operator<<(const CPointx<T>& point) {return *this;}
    template <typename T> Logger& operator<<(T value)
    {
        static_assert(std::is_arithmetic<T>::value || std::is_integral<T>::value || std::is_enum<T>::value, "This method is only meant for arithmetic types");
        return *this;
    }

    template <typename T>
    Logger& operator<<(const T* p)
    {
        *this << (uint64_t)p;
        return *this;
    }
};

int main()
{
    Logger() << CSizex<int>();
}