#include <utility>
#include <tuple>

template<typename Derived>
struct perfect_functor {
    using perfect_functor_base = perfect_functor;

    template<typename Self = Derived, typename... Args>
    auto operator()(Args&&... args) &
    -> decltype( Self::call(static_cast<Self&>(*this), std::forward<Args>(args)...) )
    { return Self::call(static_cast<Self&>(*this), std::forward<Args>(args)...); }

    template<typename Self = Derived, typename... Args>
    auto operator()(Args&&... args) const&
    -> decltype( Self::call(static_cast<Self const&>(*this), std::forward<Args>(args)...) )
    { return Self::call(static_cast<Self const&>(*this), std::forward<Args>(args)...); }

    template<typename Self = Derived, typename... Args>
    auto operator()(Args&&... args) &&
    -> decltype( Self::call(static_cast<Self&&>(*this), std::forward<Args>(args)...) )
    { return Self::call(static_cast<Self&&>(*this), std::forward<Args>(args)...); }
};

template<typename T>
using PerfectFunctorBase = typename T::perfect_functor_base;

template<typename... T>
struct defer_type: perfect_functor<defer_type<T...>> {
    using value_type = std::tuple<T...>;

    explicit defer_type(T... t)
        : deferred_values(std::forward<T>(t)...)
    {}

    value_type deferred_values;

private:
    friend PerfectFunctorBase<defer_type>;

    template<typename Self, std::size_t... Indices>
    static auto do_call(Self&& self, std::index_sequence<0, Indices...>)
    { return std::get<0>(std::move(self).deferred_values)(std::get<Indices>(std::move(self).deferred_values)...); }

    template<typename Self>
    static auto call(Self&& self)
    { return do_call(std::forward<Self>(self), std::make_index_sequence<std::tuple_size<value_type>::value>()); }
};

struct move_only {
    move_only() = default;
    move_only(move_only&&) = default;
};

int main()
{
    auto f = [](move_only m) { return std::move(m); };
    defer_type<decltype(f)&, move_only> d(f, move_only {});
    d();
}