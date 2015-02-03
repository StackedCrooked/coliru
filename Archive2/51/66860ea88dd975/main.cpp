#include <string>
#include <vector>
#include <iostream>
#include <utility>


struct Hello
{
    int helloworld(int x)  { return 0; }
    int helloworld(std::vector<int> x) { return 0; }
};

struct Generic {};



    // use std::void_t in C++... 17 I think? ... instead of this:
    template<class...>struct void_type { using type = void; };
    template<class...Ts>using void_t = typename void_type<Ts...>::type;

    template<class T, class...Args>
    using hello_world_ify = decltype(
          std::declval<T>().helloworld( std::declval<Args>()... )
    );

    template<class T, class Sig, class=void>
    struct has_helloworld:std::false_type{};

    template<class T, class...Args>
    struct has_helloworld<T, void(Args...),
      void_t<
        hello_world_ify<T, Args...>
      >
    >:std::true_type{};

    template<class T, class R, class...Args>
    struct has_helloworld<T, R(Args...),
      typename std::enable_if<
        std::is_convertible<
          hello_world_ify<T, Args...>,
          R
        >::value
      >::type
    >:std::true_type{};


int main()
{
    std::cout << has_helloworld<Hello, void(int)>::value << '\n';
    std::cout << has_helloworld<Hello, double(int)>::value << '\n';
    std::cout << has_helloworld<Hello, Generic(int)>::value << '\n';
    std::cout << '\n';
    std::cout << has_helloworld<Hello, void(std::vector<int>)>::value << '\n';
    std::cout << '\n';
    std::cout << has_helloworld<Generic, void(int)>::value << '\n';
    std::cout << has_helloworld<Generic, int(int)>::value << '\n';
    return 0;
}