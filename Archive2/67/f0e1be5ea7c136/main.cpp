    #include<iostream>
    #include<type_traits>

    struct A{};
    struct B{};
    struct C{};

    template<typename T>
    struct is_allowed
    {
        static const bool value = std::is_same<T,A>::value
                               || std::is_same<T,B>::value
                               || std::is_same<T,C>::value;
    };
    
    template <typename ... Args>
    struct Convert;
    
    template <typename T>
    struct Convert<T,T> {
        static_assert(is_allowed<T>::value,"type not allowed");
        static int param() { return 0; }
    };
    
    template <typename T, typename U>
    struct Convert<T,U> {
        static_assert(is_allowed<T>::value && is_allowed<U>::value,"type not allowed");
        static int param() { return -Convert<U,T>::param(); }
    };
        
    template <>
    struct Convert<A,B> {
        static int param() { return 42; }
    };
    
    template <>
    struct Convert<A,C> {
        static int param() { return 43; }
    };

    template <>
    struct Convert<B,C> {
        static int param() { return 44; }
    };
    
    int main()
    {
        std::cout<<Convert<A,B>::param()<<std::endl;
        std::cout<<Convert<B,A>::param()<<std::endl;
        std::cout<<Convert<A,C>::param()<<std::endl;
        std::cout<<Convert<C,A>::param()<<std::endl;
        std::cout<<Convert<B,C>::param()<<std::endl;
        std::cout<<Convert<C,B>::param()<<std::endl;
        
        Convert<int,double>::param();
    }

