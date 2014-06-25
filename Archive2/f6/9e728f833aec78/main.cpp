template <typename T>
struct promote_me_smart {
    using type = decltype(+T());
};