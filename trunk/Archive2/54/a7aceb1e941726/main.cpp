#include <type_traits>

template<class T>
struct foo
{
    static_assert(std::is_integral<T>{}, "T must be integral");
};

template<class T> struct bar {};

template<class T, class Stream>
Stream& operator<<(Stream& p, foo<T> const&);

template<class T, class Stream>
Stream& operator<<(Stream& p, bar<T> const&);

int main()
{
    int x;
    operator<< <double>(x, 1.0);
}