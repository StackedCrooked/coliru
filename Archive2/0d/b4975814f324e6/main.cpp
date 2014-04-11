#include <iostream>
#include <tuple>
#include <map>
#include <type_traits>

template <typename function_t, typename...Args>
typename std::result_of<function_t(Args...)>::type
memoize(function_t f, Args&&...a) {
    static std::map<std::tuple<function_t,Args...>, typename std::result_of<function_t(Args...)>::type> computed;
    std::tuple<function_t,Args...> arg_tuple = std::make_tuple(*f,a...);
    auto search = computed.find(arg_tuple);
    if (search != computed.end()) {
        return search->second;
    } else {
        return computed[arg_tuple] = f(a...);
    }
}

long long fibonacci(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
     static_assert(std::is_same<std::result_of<decltype(&fibonacci)(int)>::type,long long>::value,"Type mismatch!\n");
    return memoize<decltype(&fibonacci),int>(fibonacci,n-1)
         + memoize<decltype(&fibonacci),int>(fibonacci,n-2);
}

int main() {
    int val = 50;
    static_assert(std::is_same<std::result_of<decltype(&fibonacci)(int)>::type,long long>::value,"Type Mismatch!\n");
    std::cout << "fibonacci(" << val <<") = " << memoize<decltype(&fibonacci), int>(fibonacci,std::move(val)) << std::endl;
}