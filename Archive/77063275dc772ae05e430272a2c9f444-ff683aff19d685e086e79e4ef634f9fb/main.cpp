    #include <string>
    #include <iostream>
    #include <type_traits>

    template<typename T, typename V = bool>
    struct has_value : std::false_type { };

    template<typename T>
    struct has_value<T,
        typename std::enable_if<
            !std::is_same<decltype(std::declval<T>().value), void>::value,
            bool
            >::type
        > : std::true_type
    {
        typedef decltype(std::declval<T>().value) type;
    };

    void fun (const std::initializer_list<std::string>& strings) {
        for(auto s : strings)
        {
            std::cout << s << " ";
        }
    }

    template<typename T>
    struct check_has_value
    {
        static_assert(has_value<T>::value, "!");
    };

    template<typename ...Args>
    void foo () {
        auto l = { (check_has_value<Args>(), 0)... };
        fun({Args::value...});
    }

    struct A { static std::string value; };
    struct B { static std::string value; };
    struct C { static std::string value; };
    struct D { static std::string value; };

    std::string A::value = "Hello";
    std::string B::value = "World";
    std::string C::value = "of";
    std::string D::value = "Variadic Templates";

    int main()
    {
        foo<A, B, C, D>(); // where A, B, C, D are classes
    }
