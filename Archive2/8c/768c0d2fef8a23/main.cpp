#if defined(_MSC_VER) && _MSC_VER < 1400
#define GEN_MEMBER_CHECKER(Prefix, Member)                                                                  \
    template<class T> struct Prefix##Member                                                             \
    { enum { __if_not_exists(T::Member) { value = 0 } __if_exists(T::Member) { value = 1 } }; };
#else
#define GEN_MEMBER_CHECKER(Prefix, Member)                                                                  \
    template<class T> struct Prefix##Member;                                                            \
    template<class T> struct Prefix##Member<T const> : Prefix##Member<T> { };                           \
    template<class T> struct Prefix##Member<T volatile> : Prefix##Member<T> { };                        \
    template<class T> struct Prefix##Member<T &> : Prefix##Member<T> { };                               \
    template<class T> struct Prefix##Member<T *> { enum { value = 0 }; };                               \
    template<> struct Prefix##Member<void>                                                              \
    {                                                                                                   \
    private:                                                                                            \
        template<class T> static unsigned char (&test(int, T const          &))[1U + 1U];           \
        template<class T> static unsigned char (&test(int, T const volatile &))[1U + 1U];           \
        static unsigned char (&test(int, ...))[1U];                                                 \
    public:                                                                                             \
        template<class T>                                                                           \
        static unsigned char (&check(int, Prefix##Member<T> *))[1U + sizeof(test(0, &T::Member))];  \
        static unsigned char (&check(int, ...))[1U];                                                \
    };                                                                                                  \
    template<class T> struct Prefix##Member                                                             \
    { enum { value = sizeof(Prefix##Member<void>::check(0, (Prefix##Member *)0)) > 2U }; }
#endif

#include <iostream>

struct A { int x; };
struct B { const char x; };
struct C { void x() volatile ; };
struct D : A { };
struct E {};
struct F : A, B {};

GEN_MEMBER_CHECKER(has_, x);

int main()
{
    std::cout
        << has_x<A>::value
        << has_x<const B>::value
        << has_x<volatile C>::value
        //<< has_x<const volatile D>::value // error, ambiguous partial specialization
        << has_x<E>::value
        << has_x<F>::value;
}
