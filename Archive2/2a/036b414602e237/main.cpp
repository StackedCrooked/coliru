#include <tuple>

template<typename T>
struct foo;     // unimplemented primary template

template<typename Result, typename...Args>
struct foo<Result(Args...)>
{
    using args_t = std::tuple<Args...>;
};

#include <string>
#include <type_traits>

void bar(std::string, float, char) {}

int main()
{
    static_assert(std::is_same<foo<decltype(bar)>::args_t,
                                   std::tuple<std::string, float, char>
                              >::value, "Oops");
}
