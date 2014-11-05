#include <type_traits>
#include <utility>
#include <functional>

template <class, class F, class R, class... Types>
    struct is_callable_impl :
        std::false_type {};
template <class F, class R, class... Types>
    struct is_callable_impl<decltype(static_cast<R>(std::declval<F>()(std::declval<Types>()...)), void()), F, R, Types...> :
        std::true_type {};

template <class F, class R, class... Types>
    struct is_callable :
        is_callable_impl<void, F, R, Types...> {};

#include <iostream>
#define PRINT_VALUE(...) (std::cout << #__VA_ARGS__ " = " << (__VA_ARGS__) << std::endl)

typedef void F1(int);

struct F2
{
    char* operator ()(int) const;
};

int main()
{
    std::string object1;
    int object2;
    
    auto lambda = []{return "object";};
    auto lambda1 = []{return 1;};
    
    std::function<std::string()> func1 = [=]{return "object";};
    
    PRINT_VALUE(is_callable<decltype(object1), std::string>());   
    PRINT_VALUE(is_callable<decltype(object2), std::string>());
    PRINT_VALUE(is_callable<decltype(lambda), std::string>());
    PRINT_VALUE(is_callable<decltype(lambda1), std::string>());
    PRINT_VALUE(is_callable<decltype(lambda1), std::string, int>());
    PRINT_VALUE(is_callable<decltype(func1), std::string>());
    PRINT_VALUE(is_callable<decltype(func1), std::string, int>());
}