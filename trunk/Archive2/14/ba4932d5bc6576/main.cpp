#include <iostream>
#include <type_traits>
#include <utility>

template <typename T> struct CSizex {
};

struct CSize : public CSizex<int> 
{
};

namespace detail
{
    template <template <typename...> class Base, typename Derived>
    struct is_derived_from_template
    {
        using U = typename std::remove_cv<
                                  typename std::remove_reference<Derived>::type
                                >::type;

        template <typename... Args>
        static auto test(Base<Args...>*)
            -> typename std::integral_constant<bool
                                          , !std::is_same<U, Base<Args...>>::value>;

        static std::false_type test(void*);

        using type = decltype(test(std::declval<U*>()));
    };
}

template <template <typename...> class Base, typename Derived>
using is_derived_from_template = typename detail::is_derived_from_template<Base, Derived>::type;

struct Logger
{
    template <typename T> 
    typename std::enable_if<!is_derived_from_template<CSizex, typename std::decay<T>::type>::value, Logger&>::type operator<< (T& value)
    {
        std::cout << "operator<< (T& value)" << std::endl;
        return *this << const_cast<const T & >(value);
    }

    template <typename T>
    Logger& operator<<(const CSizex<T>& size)
    {
        std::cout << "operator<<(const CSizex<T>& size)" << std::endl;
        return *this;
    }

    template <typename T> 
    typename std::enable_if<!is_derived_from_template<CSizex, typename std::decay<T>::type>::value, Logger&>::type operator<< (const T& value)
    {
        static_assert(std::is_arithmetic<T>::value || std::is_integral<T>::value || std::is_enum<T>::value, "This method is only meant for arithmetic types");
        std::cout << "operator<<(const T& value)" << std::endl;
        return *this;
    }
};

int main()
{
    CSize size;
    Logger() << size;
    Logger() << CSize();
    Logger() << CSizex<int>();
    Logger() << CSizex<float>();
    Logger() << 123;
}
