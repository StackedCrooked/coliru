#include <type_traits>

template <typename T, typename = void>
struct is_equality_comparable : std::false_type {};

template <typename T>
struct is_equality_comparable<T,
        typename std::enable_if<
          std::is_convertible<decltype(std::declval<T&>() == std::declval<T&>())
        , bool>{}>::type
        > : std::true_type {};

template <typename T, typename = void>
struct is_less_than_comparable : std::false_type {};

template <typename T>
struct is_less_than_comparable<T,
        typename std::enable_if<
          std::is_convertible<decltype(std::declval<T&>() < std::declval<T&>())
        , bool>{}>::type
        > : std::true_type {};

// sample equlity comparable type with **member** operator==
struct EqComparable
{
    bool operator==(const EqComparable& other)
    {
        return i == other.i;
    }

    int i;
};

// sample less-than comparable type with **global** operator<
struct LessThanComparable
{
    int i;
};

bool operator<(const LessThanComparable& lhs, const LessThanComparable& rhs)
{
    return lhs.i < rhs.i;
}

// sample class which is not comparable in any way
struct NotComparableAtAll
{
};

// your template classes with constraints:

template <typename T>
class MustBeEqComparable
{
    static_assert(is_equality_comparable<T>::value, "Type T is not equality comparable!");
};

template <typename T>
class MustBeLessThanComparable
{
    static_assert(is_less_than_comparable<T>::value, "Type T is not less than comparable!");
};

int main()
{
    MustBeEqComparable<EqComparable> a;

    MustBeEqComparable<NotComparableAtAll> b; // issues error

    MustBeLessThanComparable<LessThanComparable> c;

    MustBeLessThanComparable<NotComparableAtAll> d; // issues error
}
