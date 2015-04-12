#include <type_traits>

template<typename... Items>
struct typelist;

template<typename Typelist>
struct car;

template<typename Head, typename... Remainder>
struct car<typelist<Head, Remainder...>>
{
    using type = Head;
};

template<typename Typelist>
struct cdr;

template<typename Head, typename... Remainder>
struct cdr<typelist<Head, Remainder...>>
{
    using type = typelist<Remainder...>;
};

template<typename Lhs, typename Rhs>
struct concat;

template<typename... LeftSeq, typename... RightSeq>
struct concat<
    typelist<LeftSeq...>,
    typelist<RightSeq...>
>
{
    using type = typelist<LeftSeq..., RightSeq...>;
};

template<typename Source, typename Comparand>
struct compare
{
    constexpr static bool value = false;
};

template<typename Source>
struct compare<Source, typelist<>>
{
    constexpr static bool value = true;
};

template<typename Head, typename... SourceRemainder, typename... ComparandRemainder>
struct compare<typelist<Head, SourceRemainder...>, typelist<Head, ComparandRemainder...>>
{    
    constexpr static bool value = compare<
        typelist<SourceRemainder...>,
        typelist<ComparandRemainder...>
    >::value;
};

template<typename Lhs, typename Rhs>
struct subtract;

template<
    typename LhsHead, typename... LhsRemainder,
    typename RhsHead, typename... RhsRemainder
>
struct subtract<
    typelist<LhsHead, LhsRemainder...>,
    typelist<RhsHead, RhsRemainder...>
>
{
    using type = typename subtract<
        typelist<LhsRemainder...>,
        typelist<RhsRemainder...>
    >::type;
};

template<typename Lhs>
struct subtract<Lhs, typelist<>>
{
    using type = Lhs;
};

template<typename Lhs, typename Rhs>
struct subtract;


template<typename Source, typename Old, typename New>
struct subst;

template<typename New>
struct subst<typelist<>, typelist<>, New>
{
    using type = typelist<>;
};

template<typename Old, typename New>
struct subst<typelist<>, Old, New>
{
    using type = typelist<>;
};

template<typename Source, typename New>
struct subst<Source, typelist<>, New>
{
    using type = Source;
};

template<bool branch, typename Source, typename Old, typename New>
struct subst_if;

template<
    typename SourceHead, typename... SourceRemainder,
    typename Old, typename New
>
struct subst_if<
    true,
    typelist<SourceHead, SourceRemainder...>,
    Old, New
>
{
    using type = typename concat<
        New,
        typename subst<
            typename subtract<
                typelist<SourceHead, SourceRemainder...>,
                Old
            >::type,
            Old,
            New
        >::type
    >::type;
};

template<
    typename SourceHead, typename... SourceRemainder,
    typename Old, typename New
>
struct subst_if<
    false,
    typelist<SourceHead, SourceRemainder...>,
    Old, New
>
{
    using type = typename concat<
        typelist<SourceHead>,
        typename subst<
            typelist<SourceRemainder...>,
            Old,
            New
        >::type
    >::type;
};

template<typename Source, typename Old, typename New>
struct subst
{
    using type = typename subst_if<
        compare<
            Source,
            Old
        >::value,
        Source,
        Old,
        New
    >::type;
};

struct _0;
struct _1;
struct _2;
struct _3;
struct _4;
struct _5;

static_assert(compare<typelist<_0, _1, _2, _3>, typelist<_0, _1>>::value, "");
static_assert(!compare<typelist<_0, _2, _3>, typelist<_0, _1>>::value, "");
static_assert(std::is_same<
    typename subst<
        typelist<_0>,
        typelist<_0>,
        typelist<_1>
    >::type,
    typelist<_1>
>::value
,"");
static_assert(std::is_same<
    typename subst<
        typelist<_0, _1, _2, _3, _4, _5>,
        typelist<_2, _3>,
        typelist<_4, _5>
    >::type,
    typelist<_0, _1, _4, _5, _4, _5>
>::value
,"");
static_assert(std::is_same<
    typename subst<
        typelist<_0, _1, _3, _4, _5>,
        typelist<_2, _3>,
        typelist<_4, _5>
    >::type,
    typelist<_0, _1, _3, _4, _5>
>::value
,"");
static_assert(std::is_same<
    typename subst<
        typelist<_0, _1, _2, _3, _4, _5, _2, _3>,
        typelist<_2, _3>,
        typelist<_4, _5>
    >::type,
    typelist<_0, _1, _4, _5, _4, _5, _4, _5>
>::value
,"");
static_assert(std::is_same<
    typename subst<
        typelist<_0, _1, _2, _3, _4, _5>,
        typelist<_0, _1, _2, _3, _4, _5>,
        typelist<_4, _5>
    >::type,
    typelist<_4, _5>
>::value
,"");


int main()
{
}