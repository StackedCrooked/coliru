    #include <iostream>
    #include <functional>
    #include <type_traits>
    
    template<typename F>
    struct first_argument {
      template<typename Ret, typename A, typename... Rest>
      static A  helper(Ret (F::*)(A, Rest...));
      template<typename Ret, typename A, typename... Rest>
      static A helper(Ret (F::*)(A, Rest...) const);
      typedef decltype(helper(&F::operator())) type;
    };
    
    template <typename T>
    static void foo(T f) {
        typedef typename first_argument<T>::type type;
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
        const int i = 9;
        foo([i](const bool value) {
            std::cout << std::boolalpha << value << ':' << i << std::endl;
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