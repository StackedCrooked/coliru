#include <boost/operators.hpp>
#include <iostream>
#include <string>
#include <map>

#define STRONG_TYPEDEF(T, Name) \
    struct Name : boost::operators<Name> { \
        Name() : t() {} \
        explicit Name(const T & t_) : t(t_) {} \
        operator const T & () const { return t; } \
        operator T & () { return t; } \
        bool operator==(const Name & rhs) const { return t == rhs.t; } \
        bool operator<(const Name & rhs) const { return t < rhs.t; } \
        T t; \
    }
    

STRONG_TYPEDEF(int, X);
STRONG_TYPEDEF(int, Y);


int main()
{
    std::map<X, Y> map;
    return map.size();
}
