    #include <type_traits>
    #include <cstdio>

    template<class E, class Enable = void>
    struct to_integral_helper
    {
        static E inner(E e)
        {
            return e;
        }
    };

    template<typename E>
    struct to_integral_helper<E, typename std::enable_if<std::is_enum<E>::value>::type>
    {
        static typename std::underlying_type<E>::type inner(E e)
        {
            return static_cast<typename std::underlying_type<E>::type>(e);
        }
    };

    template<typename T>
    auto to_integral(T t) -> decltype(to_integral_helper<T>::inner(t))
    {
        return to_integral_helper<T>::inner(t);
    }

    enum class MyEnum { A = 5 };
    
    int main()
    {
        auto a = to_integral(42);
        auto b = to_integral(MyEnum::A);
        printf("%d\n", a);
        printf("%d\n", b);
    }
