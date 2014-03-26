#include <type_traits>
#include <iostream>

template<typename Type>
struct tag {};

struct Atag {};
struct Btag {};

template<typename Type, typename Tag>
struct tag_enabled
{
    static const bool value = std::is_same
    <
        typename tag<Type>::type,
        Tag
    >::value;

    /*  TYPEDEF REMOVED */
};

template<typename A, typename B>
typename std::enable_if
<
    tag_enabled<A, Atag>::value &&
    tag_enabled<B, Btag>::value,
    A
>::type
worker(
    B const & b
)
{
    A result;

    std::cout << "Btag -> Atag" << std::endl;

    return result;
}

template<typename A, typename B>
typename std::enable_if
<
    tag_enabled<A, Atag>::value &&
    tag_enabled<B, Atag>::value,
    A
>::type
worker(
   B const & b
)
{
    A result;

    std::cout << "Atag -> Atag" << std::endl;

    return result;
}

struct test_a {};
struct test_b {};

template<>
struct tag<test_a>
{
    typedef Atag type;
};

template<>
struct tag<test_b>
{
    typedef Btag type;
};

int main()
{
    test_a ta1;
    test_b tb1;

    auto ta2 = worker<test_a>(ta1);
    auto ta3 = worker<test_a>(tb1);

    return 0;
}
