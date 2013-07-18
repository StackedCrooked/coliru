namespace detail
{
    template <typename... T> struct last_of;

    template <typename T>
        struct last_of<T> {
            constexpr static auto exec(T const& v) -> T 
            { return v; }
        };

    template <typename T, typename... Ts> 
        struct last_of<T, Ts...> {
            constexpr static auto exec(T const&, Ts const&... ts) -> decltype(last_of<Ts...>::exec(ts...)) 
            { return last_of<Ts...>::exec(ts...); }
        };
};

template <typename... T> 
    constexpr auto last_of(T const&... ts) -> decltype(detail::last_of<T...>::exec(ts...))
{
    return detail::last_of<T...>::exec(ts...);
}

int main()
{
    return last_of(false,100.f,"8",-9,42);
}
