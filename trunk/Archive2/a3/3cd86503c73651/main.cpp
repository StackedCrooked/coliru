#include <cstdio>


struct StdOut{};


#define FORMAT_SPECIFIERS(x) \
    x(const char*, "%s" ) \
    x(char       , "%c" ) \
    x(int        , "%d" ) \
    x(float      , "%f" ) \
    x(double     , "%lf")

#define x(type, format) \
    void print(type t) { printf(format, t); }
    FORMAT_SPECIFIERS(x)
#undef x
#undef FORMAT_SPECIFIERS


template<typename T>
StdOut&& operator<<(StdOut&& out, const T& t)
{
    return print(t), (decltype(out))(out);
}


int main()
{
    StdOut() << "abc=" << 123 << "\ndef=" << 456 << '\n';
}
