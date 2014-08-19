#include <type_traits>
#include <utility>

template<typename Functor>
struct fix_type {
    Functor functor;
    
    template<typename... Args>
    auto operator()(Args&&... args) &
    -> decltype( functor(functor, std::forward<Args>(args)...) )
    { return functor(functor, std::forward<Args>(args)...); }
    
    template<typename... Args>
    auto operator()(Args&&... args) const&
    -> decltype( functor(functor, std::forward<Args>(args)...) )
    { return functor(functor, std::forward<Args>(args)...); }
    
    template<typename... Args>
    auto operator()(Args&&... args) &&
    -> decltype( std::move(functor)(std::move(functor), std::forward<Args>(args)...) )
    { return std::move(functor)(std::move(functor), std::forward<Args>(args)...); }
};

template<typename Functor>
fix_type<typename std::decay<Functor>::type> fix(Functor&& functor)
{ return { std::forward<Functor>(functor) }; }

#include <cassert>

struct factorial_type {
    template<typename Self>
    int operator()(Self&& self, int n) const
    { return n < 2 ? 1 : n * self(self, n - 1); }
};

int main()
{
    auto factorial = fix(factorial_type {});
    assert( factorial(5) == 120 );
}