#include <iostream>
#include <map>
#include <set>
#include <utility>
#include <valarray>

template <template <typename ...> class P, typename ... Args>
struct c
{
    using type = P<Args...>; 
    static const std::size_t count = sizeof...(Args);

    static void f(const type &t)
    {
        std::cout << "Template with " << sizeof...(Args) << " parameters!\n";
    }
};

template <template <typename, typename> class P, typename A, typename B>
struct c<P, A, B> 
{
    using type = P<A, B>; 

    static void f(const type &t)
    {
        std::cout << "Spezialized 2 parameters!\n";
    }
};

template <template <class ...> class P, class... Args>
void f(const P<Args...> &t)
{
    c<P, Args...>::f(t);
}

int main()
{
    f(std::valarray<int>{});
    f(std::pair<char, char>{});
    f(std::set<float>{});
    f(std::map<int, int>{});
}