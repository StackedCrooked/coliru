template<class...> struct types{ using type = types; };

template<class Acc, class... Types>
struct reversed_ : Acc{};

template<class... RTypes, class Head, class... Tail>
struct reversed_<types<RTypes...>, Head, Tail...> : reversed_<types<Head, RTypes...>, Tail...>{};

template<class... Ts>
struct reversed : reversed_<types<>, Ts...>{};

int main()
{
    struct {} _ = reversed<char>::type();
    struct {} __ = reversed<char, int>::type();
}
