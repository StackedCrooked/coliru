template<unsigned... Is> struct seq{};

template<unsigned I, unsigned... Is>
struct gen_seq{
    using type = typename gen_seq<I-1, I-1, Is...>::type;
};

template<unsigned... Is>
struct gen_seq<0, Is...>{
    using type = seq<Is...>;
};