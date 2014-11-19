#include<iostream>

    template <typename ... Args>
    struct Convert;
    
    template <typename T>
    struct Convert<T> {
        static int param() { return 0; }
    };
    
    template <typename T, typename U>
    struct Convert<T,U> {
        static int param() { return -Convert<U,T>::param(); }
    };
    
    struct A{};
    struct B{};
    struct C{};
    
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
    }
