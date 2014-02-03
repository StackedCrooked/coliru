enum bla {
    foo,
    bar,
    baz
};

template<bla Value> struct bla_to_type_t{};
template<> struct bla_to_type_t<foo>{using type = char;};
template<> struct bla_to_type_t<bar>{using type = short;};
template<> struct bla_to_type_t<baz>{using type = int;};

template<bla Value>
using bla_to_type = typename bla_to_type_t<Value>::type;


int main() {}