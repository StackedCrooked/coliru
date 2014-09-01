#include <iostream>

#define ASSERT(expr, ...) resolve(#expr, expr, cPH(__VA_ARGS__))

void print(const char str[], bool val)
{
    std::cout << (val ? "passed: " : "failed: ");
    std::cout << str;
    std::cout << std::endl;
}

void print(const char str[], bool val, const char descr[])
{
    std::cout << (val ? "passed: " : "failed: ");
    std::cout << str;
    std::cout << " (" << descr << ')';
    std::cout << std::endl;
}

void print(const char str[], bool val, int severity)
{
    std::cout << (val ? "passed: " : "failed: ");
    std::cout << str;
    std::cout << " (#" << severity << ')';
    std::cout << std::endl;
}

template <typename T>
struct PH
{
    typedef T raw;

    PH(const T &v) : v(v) { }

    operator T() const { return v; }

    const T &v;
};

template <int N>
struct PH<char[N]>
{
    typedef const char * raw;

    PH(const char *v) : v(v) { }

    operator const char *() const { return v; }

    const char *v;
};

template <>
struct PH<void>
{
};

PH<void> cPH()
{
    return PH<void>();
}

template <typename T>
PH<T> cPH(const T &a)
{
    return PH<T>(a);
}

template <typename A, typename B, typename C>
void resolve(const A &a, const B &b, const PH<C> &c)
{
    print(a, b, static_cast<typename PH<C>::raw>(c));
}

template <typename A, typename B>
void resolve(const A &a, const B &b, PH<void>)
{
    print(a, b);
}

int
main(void)
{
    ASSERT(true && true && true);
    ASSERT(true && true && true, "is always true");
    ASSERT(true && true && true, 12);
    ASSERT(true && false);
    ASSERT(true && false, "actually false");
    return 0;
}