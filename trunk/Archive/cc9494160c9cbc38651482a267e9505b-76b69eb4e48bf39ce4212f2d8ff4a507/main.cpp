template<class T> struct int_{ using type = int; };

template<class T> using Int = typename int_<T>::type;

template<class T, class... Ts>
struct back{
    template<Int<Ts>..., class U>
    static U* select(){}
    
    using type = decltype(select<Int<T>(), Int<Ts>()...>());
};

template<class T, class U>
struct is_same{ static constexpr bool value = false; };
template<class T>
struct is_same<T,T>{ static constexpr bool value = true; };

static_assert(is_same<back<int, bool, float>::type, float(*)()>::value, "...");

int main(){}