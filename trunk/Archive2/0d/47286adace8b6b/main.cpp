#include <type_traits>

// the naive definition
template<class Call> struct result_of{}; // doesn't matter if defined or not

template<class F, class... Args>
struct result_of<F(Args...)>{
  using type = decltype(std::declval<F>()(std::declval<Args>()...));
};

template<class Call>
typename result_of<Call>::type f(int){}

template<class>
void f(...){}

int main()
{
    using fty = void(*)(int&);
    f<fty(int&)>(0);
    f<fty(int)>(0);
}