    #include <iostream>
    #include <functional>
    #include <type_traits>
    
    template<typename T>
    struct functor_param;
    
    template<class R, class C, class T>
    struct functor_param<R (C::*)(T)> {
        typedef T type;
    };
    
    template<class R, class C, class T>
    struct functor_param<R (C::*)(T) const> {
        typedef T type;
    };
    
    template<class T>
    typename functor_param<T>::type functor_param_helper(T);
    
    template <typename T>
    static void foo(T f) {
        typedef decltype(functor_param_helper(&T::operator())) type;
        std::cerr << "using traits overload" << std::endl;
        std::cerr << "typename: " << typeid(type).name() << std::endl;
        f(true);
    }
    
    template<typename T>
    static void foo(void (*f)(const T)) {
        std::cerr << "using function pointer overload" << std::endl;
        std::cerr << "typename: " << typeid(T).name() << std::endl;
        f(T());
    }
    
    
    int main() {
        const bool x = false;
        foo([](const bool value) {
            std::cout << std::boolalpha << value << std::endl;
        });
        foo(+[](const bool value) {
            std::cout << std::boolalpha << value << std::endl;
        });
        foo(+[](const int value) {
            std::cout << value << std::endl;
        });
        foo([&x](const bool value) {
            std::cout << std::boolalpha << value << '|' << x << std::endl;
        });
        return 0;
    }