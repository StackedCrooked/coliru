
template<typename... Ts>
struct MetafunctionClass1
{
    template<typename... Args>
    struct apply
    {
        using type = int;
    };
};

template<typename... Ts>
struct MetafunctionClass2
{
    template<typename... Args>
    struct apply
    {
        using result = int;
    };
};

template<typename T, typename... Args>
using get_apply = typename T::template apply<Args...>;

template<typename T, typename = void>
struct call;

template<typename T>
struct call<T, typename T::result>
{
    using type = typename T::result;  
};

template<typename T>
struct call<T, typename T::type>
{
    using type = typename T::type;  
};

template<typename T, typename... Args>
using call_metafunction_class = typename call<get_apply<T, Args...>>::type;

struct X {}; //Just a placeholder

using result1 = call_metafunction_class<MetafunctionClass1<X,X>,int,int,int>;
using result2 = call_metafunction_class<MetafunctionClass2<X,X>,int,int,int>;

int main()
{
    result1 a = 0;
    result2 b = 0;
}
