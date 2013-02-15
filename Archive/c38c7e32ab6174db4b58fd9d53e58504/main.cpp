template <typename... T>
struct typelist {
    static constexpr bool size = sizeof...(T);
};
using nil = typelist<>;
template <typename Head, typename... Tail>
struct typelist<Head, Tail...> {
    using head = Head;
    using tail = typelist<Tail...>;
    static constexpr bool size = sizeof...(Tail)+1;
};

int main() {}