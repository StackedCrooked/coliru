#include <utility>

template<typename Derived>
struct perfect_functor {
    using perfect_functor_base = perfect_functor;

    template<typename Self = Derived, typename... Args>
    auto delegate_call(Args&&... args) &
    -> decltype( Self::call(static_cast<Self&>(*this), std::forward<Args>(args)...) )
    { return Self::call(static_cast<Self&>(*this), std::forward<Args>(args)...); }

    template<typename Self = Derived, typename... Args>
    auto delegate_call(Args&&... args) const&
    -> decltype( Self::call(static_cast<Self const&>(*this), std::forward<Args>(args)...) )
    { return Self::call(static_cast<Self const&>(*this), std::forward<Args>(args)...); }

    template<typename Self = Derived, typename... Args>
    auto delegate_call(Args&&... args) &&
    -> decltype( Self::call(static_cast<Self&&>(*this), std::forward<Args>(args)...) )
    { return Self::call(static_cast<Self&&>(*this), std::forward<Args>(args)...); }
};

template<typename T>
using PerfectFunctorBase = typename T::perfect_functor_base;

template<typename T>
struct defer_type: perfect_functor<defer_type<T>> {
    explicit defer_type(T t)
        : value(std::forward<T>(t))
    {}

    T value;

private:
    friend PerfectFunctorBase<defer_type>;

    template<typename Self>
    static auto call(Self&& self)
    { self.value.i += 3; }
};

struct move_only {
    move_only() = default;
    move_only(move_only&&) = default;
    move_only& operator=(move_only&&) = default;
    
    int i;
};

int main()
{
    move_only m; m.i = 42;
    defer_type<move_only> d(std::move(m));
    d.delegate_call();
}