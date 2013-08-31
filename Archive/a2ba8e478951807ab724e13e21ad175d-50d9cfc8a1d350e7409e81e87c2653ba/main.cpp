template<
    typename R, typename F, typename V, typename... Vs,
    EnableIf<
        Not<is_deduced<R>>,
        Or<
            is_variant<Unqualified<V>>,
            is_variant<Unqualified<Vs>>...
        >
    >...
>
