#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <type_traits>

// details
template<typename El, typename Tuple, int Index, int Size> struct IndexOf_
{
    static constexpr int value = std::is_same<typename std::tuple_element<Index, Tuple>::type, El>::value ? Index : IndexOf_<El, Tuple, Index + 1, Size>::value;
};

template<typename El, typename Tuple, int Index> struct IndexOf_<El, Tuple, Index, Index>
{
    static constexpr int value = -1;
};

template<typename T, typename ...TupleTypes> struct IndexOf;

template<typename T, typename ...TupleTypes> struct IndexOf<T, std::tuple<TupleTypes...> >
{
    typedef std::tuple<TupleTypes...> tuple_type;
    static constexpr int tuple_size = std::tuple_size<tuple_type>::value;
    static constexpr int value = IndexOf_<T, tuple_type, 0, tuple_size>::value;
};

template<typename T, typename ...Args> struct IsAnyOf;

template<typename T, typename argument_type> struct IsAnyOf<T, argument_type>
{
    static constexpr bool value = std::is_same<T, argument_type>::value;
};

template<typename T, typename Head, typename ...Tail> struct IsAnyOf<T, Head, Tail...>
{
    static constexpr bool value = std::is_same<T, Head>::value || IsAnyOf<T, Tail...>::value;
};

template<typename Head, typename ...Tail> struct HasDuplicates;

template<typename Head> struct HasDuplicates<Head>
{
    static constexpr bool value = false;
};

template<typename Head, typename Tail> struct HasDuplicates<Head, Tail>
{
    static constexpr bool value = std::is_same<Head, Tail>::value;
};

template<typename Head, typename Next, typename ...Tail> struct HasDuplicates<Head, Next, Tail...>
{
    static constexpr bool value = std::is_same<Head, Next>::value || IsAnyOf<Head, Tail...>::value || IsAnyOf<Next, Tail...>::value;
};

template<typename ...Args> auto MakeRecord(Args && ...args) -> std::tuple<Args...>
{
    static_assert(!HasDuplicates<Args...>::value, "The argument list must not contain two objects of same type.");
    return std::make_tuple(std::forward<Args>(args)...);
}

template<typename T, typename ...U> T & Get(std::tuple<U...> & record)
{
    static_assert(!HasDuplicates<U...>::value, "The argument list must not contain two objects of same type.");
    static constexpr unsigned index = IndexOf<T, std::tuple<U...>>::value;
    static_assert(index < (sizeof...(U)), "Out of bounds");
    return std::get< index >(record);
}

template<typename T, typename ...U> const T & Get(const std::tuple<U...> & record)
{
    static_assert(!HasDuplicates<U...>::value, "The argument list must not contain two objects of same type.");
    static constexpr unsigned index = IndexOf<T, std::tuple<U...>>::value;
    static_assert(index < (sizeof...(U)), "Out of bounds");
    return std::get< index >(record);
}

template<typename T, typename Tag> struct StrongTypedef
{
    explicit StrongTypedef(T&& t = T()) : t(std::forward<T>(t))
    {
    }
    explicit operator const T & () const
    {
        return t;
    }
    explicit operator T & ()
    {
        return t;
    }
    const T & get() const
    {
        return t;
    }
    T & get()
    {
        return t;
    }
    friend std::ostream & operator<<(std::ostream & os, const StrongTypedef<T, Tag> & obj)
    {
        return os << obj.t;
    }
    T t;
};
template<typename ...Args> struct Handy : std::tuple<Args...>
{
    template<typename ...A> Handy(A&& ...a) : std::tuple<Args...>(std::forward<A>(a)...)
    {
    }
    template<typename Strong> const Strong& get() const
    {
        return Get<Strong>(*this);
    }
    template<typename StrongType> void set(const typename StrongType::inner_type& inner)
    {
        StrongType& strong = Get<StrongType>(*this);
        strong = StrongType(inner);
    }
    template<typename StrongType> void set(const StrongType& strong)
    {
        Get<StrongType>(*this) = strong;
    }
};
using ServerId    = StrongTypedef<std::string, struct ServerId_>;
using InterfaceId = StrongTypedef<std::string, struct InterfaceId_>;
using PortId      = StrongTypedef<std::string, struct PortId_>;
using PortName    = StrongTypedef<std::string, struct PortName_>;
typedef Handy<PortId, PortName     > Port      ;
typedef std::vector<Port    > Ports        ;
typedef Handy<InterfaceId, Ports   > Interface ;
typedef std::vector<Interface > Interfaces ;
typedef Handy<ServerId, Interfaces > Server    ;
typedef std::vector<Server      > Servers  ;



int main()
{
    Server server {
        ServerId("s1"),
        Interfaces {
            Interface {
                InterfaceId("interface_1"),
                Ports {
                    { PortId("p11"), PortName("Jolly") },
                    { PortId("p12"), PortName("Billy") }
                }
            },
            Interface {
                InterfaceId("interface_2"),
                Ports {
                    { PortId("p21"), PortName("Bimbo") },
                    { PortId("p22"), PortName("Luffy") }
                }
            }
        }
    };

    auto& interfaces = server.get<Interfaces>();
    std::cout << "Interface id: " << interfaces.front().get<InterfaceId>() << std::endl;

    auto& ports = interfaces.front() .get<Ports>();
    std::cout << "Port name: " << ports.front().get<PortName>() << std::endl;
}


