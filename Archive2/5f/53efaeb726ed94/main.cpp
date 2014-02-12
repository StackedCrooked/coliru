#include <type_traits>

template<typename Target, typename Value>
struct dynamic_caster {
    typedef Value                                               value_type;
    typedef Target                                              result_type;

    static_assert(std::is_same<value_type&, const value_type&>::value, "references and shit");
};

struct foo { virtual ~foo() = default; };
struct bar : foo {};

dynamic_caster<foo&, bar&> x;

int main() {}
