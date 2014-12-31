#include <iterator>
#include <utility>
#include <type_traits>

#define show_errors 0
#define check_expr(EXPR)\
    static auto verify(int) -> decltype(EXPR);    
#define check_type(TYPE)\
    static auto verify(int) -> detail::void_t<TYPE>;
    
#if show_errors == 1
#   define error(MSG)\
        template <typename T> struct FailureMessage { static_assert(detail::ConceptFailed<T>{}, MSG); };\
        template <typename T> static auto verify(...) -> FailureMessage<T>;
#else
#   define error(MSG)
#endif

namespace detail
{
    template <typename T>
    struct ConceptFailed : std::false_type {};
    
    template <typename...>
    struct voider { using type = void; };
    
    template <typename... Ts>
    using void_t = typename voider<Ts...>::type;
}

namespace detail
{
    template <typename T>
    struct ConceptImpl;
    
    template <typename Concept, typename... Args>
    struct ConceptImpl<Concept(Args...)>
    {
        template <typename T = Concept>
        static auto test(int) -> decltype(void(T::template verify<Args...>(1)), std::true_type{});
        template <typename T = Concept>
        static auto test(...) -> std::false_type;
    };
}

template <typename T>
constexpr bool Concept = decltype(detail::ConceptImpl<T>::test(0)){};

template <typename... Ts>
constexpr bool Concepts = true;

template <typename T, typename... Ts>
constexpr bool Concepts<T, Ts...> = Concept<T> && Concepts<Ts...>;

namespace detail
{
    using std::begin;    
    struct HasBegin
    {
        template <typename T>
        check_expr(begin(std::declval<T&>()))
        error("begin(T) failed")
    };
}
using HasBegin = detail::HasBegin;

namespace detail
{
    using std::end;    
    struct HasEnd
    {
        template <typename T>
        check_expr(end(std::declval<T&>()))
        error("end(T) failed")
    };
}
using HasEnd = detail::HasEnd;

namespace detail
{
    struct HasSize
    {
        template <typename T>
        check_expr(std::declval<T&>().size())
        error("T::size() not satisfied")
    };
}
using HasSize = detail::HasSize;

namespace detail
{
    struct HasEq
    {
        template <typename T>
        check_expr(std::declval<T&>() == std::declval<T&>())
        error("T is not equality comparable")
    };
}
using HasEq = detail::HasEq;

namespace detail
{
    struct HasValueType
    {
        template <typename T>
        check_type(typename T::value_type)
        error("T::value_type is missing")
    };
}
using HasValueType = detail::HasValueType;

template <typename ContainerType>
void sort(ContainerType& container)
{
    static_assert(Concepts<HasBegin(ContainerType), HasEnd(ContainerType), HasSize(ContainerType), HasValueType(ContainerType)>
                , "Invalid container type");
}

#include <vector>
#include <list>

namespace X
{
    struct A
    {
        using value_type = int;
        size_t size() const { return 0; }
    };
    
    A* begin(A&) { return {}; }
    A* end(A&) { return {}; }
}

struct B {};

int main()
{
    std::vector<int> v; sort(v);     
    std::list<int> l; sort(l);
    X::A a; sort(a);
    B b; sort(b);
}
