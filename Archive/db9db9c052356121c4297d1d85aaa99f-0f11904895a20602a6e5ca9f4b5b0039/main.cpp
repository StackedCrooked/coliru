#include <type_traits>
#include <utility>

template<typename Functor>
struct fix_type {
    Functor functor;
    
    template<typename... Args>
    decltype(auto) operator()(Args&&... args) &
    { return functor(*this, std::forward<Args>(args)...); }
    
    template<typename... Args>
    decltype(auto) operator()(Args&&... args) const&
    { return functor(*this, std::forward<Args>(args)...); }
    
    template<typename... Args>
    decltype(auto) operator()(Args&&... args) &&
    { return std::move(functor)(std::move(*this), std::forward<Args>(args)...); }
};

template<typename Functor>
fix_type<typename std::decay<Functor>::type> fix(Functor&& functor)
{ return { std::forward<Functor>(functor) }; }

int main()
{
    auto factorial = fix([](auto&& self, int n) -> int
    { return n < 2 ? 1 : n * self(n - 1); });
    
    /* GCC may complain about this, and may be right about it
    auto factorial = fix([](auto&& self, int n)
    {
        if(n < 2) return 1;
        else return n * self(n - 1);
    });
    */
    
    return factorial(5);
}