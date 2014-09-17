    #include <type_traits>
    namespace detail
    {
        template <template <class...> class B, typename Derived>
        struct is_derived_from
        {
            using U = typename std::remove_cv<Derived>::type;
    
            template <typename... Args>
            static auto test(B<Args...>*)
                -> typename std::integral_constant<bool
                                               , !std::is_same<U, B<Args...>>::value>;
    
            static std::false_type test(void*);
    
            using type = decltype(test(std::declval<U*>()));
        };
      
        using std::is_base_of; // 
    }
    
    template <template <class...> class B, typename Derived>
      constexpr bool my_is_base_of() { return detail::is_derived_from<B, Derived>::type::value; }
    
    template <class B, typename Derived>
      constexpr bool my_is_base_of() { return detail::is_base_of<B,Derived>::value; }
    
    struct B {};
    struct D : B {};

    template<class ...>
    struct B2 {}; 
    struct D2 : B2<int, double> { };
    
    int main() {
      static_assert(my_is_base_of<B2, D2>(), "Oops");
      static_assert(my_is_base_of<B, D>(), "Oops");
      static_assert(my_is_base_of<B2<int, double>, D2>(), "Oops");
      static_assert(!my_is_base_of<B, D2>(), "Oops");
    }