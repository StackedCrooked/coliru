#include <type_traits>
#include <utility>
#include <iostream>


namespace detail
{    
    template<typename T>
    struct return_type : std::common_type<T> { };    
    
    // signature: void(argument_type...)
    template<typename F, typename ...Args>
    void call_impl(F f, return_type<void>, Args&& ...args)
    {
        f(std::forward<Args>(args)...);
    }    
    
    // signature: result_type(argument_type...)
    template<typename F, typename R, typename ...Args>
    R call_impl(F f, return_type<R>, Args&& ...args)
    {
        return f(std::forward<Args>(args)...);
    }
}


template<typename F, typename ...Args>
auto call(F f, Args&& ...args) -> decltype(f(std::forward<Args>(args)...))
{
    typedef decltype(f(std::forward<Args>(args)...)) R;
    return detail::call_impl(f, detail::return_type<R>{}, std::forward<Args>(args)...);
}


int main()
{
    // signature = void(argument_type)
    auto log = [](const std::string& s) { std::cout << "LOG: " << s << std::endl; };
    call(log, "Hello");
    
    // signature = void(void)
    auto poke = []() { std::cout << "(poke)" << std::endl; };
    call(poke);
    
    // signature = result_type(void)
    auto get_time = []() { return std::string("12:00"); };
    std::cout << "get_time: " << call(get_time) << std::endl;
    
    // signature = result_type(argument_type)
    auto int_to_string = [](int n) { return std::to_string(n); };
    std::cout << "int_to_string(2): " << call(int_to_string, 2) << std::endl;  
    
    // signature = result_type(argument_type, argument_type)
    auto sum = [](int a, int b) { return a + b; };
    std::cout << "sum(3, 4): " << call(sum, 3, 4) << std::endl;
    
    // signature = void(argument_type, argument_type, argument_type&);
    auto multiply = [](int a, int b, int& product) -> void { product = a * b; };
    int product_of_3_and_4;
    call(multiply, 3, 4, product_of_3_and_4);
    std::cout << "product_of_3_and_4: " << product_of_3_and_4 << std::endl;
    
    // signature = T&(T&)
    auto increment = [](int& n) -> int& { n++; return n; };
    int n = 42;
    int& m = call(increment, n);
    std::cout << m << std::endl;    
    
    
    std::cout << "Everything is OK." << std::endl;
}
