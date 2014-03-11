#include <type_traits>
#include <iostream>

template <typename T, bool = std::is_trivially_destructible<T>::value>
    union example {
        T t;
    
        constexpr example(const T & t) : t(t) {};
    
        /* We rely on owning class to take care
         * of destructing the active member */
        ~example() { std::cout << "primary template\n"; }
    };
    
    template<typename T>
    union example<T, true> {
        T t;
    
        constexpr example(const T & t) : t(t) {};
    };
    
    
    struct nontrivial
    {
        ~nontrivial() { std::cout << "woot!\n"; }
    };
    
    int main()
    {
        example<nontrivial> e1{{}};
        example<int> e2{{}};
    }