#include <type_traits>

template <typename T, typename UGen>
struct Base {
    using type = Base<T, typename UGen::template type<T> >;
    using devired_type = T;

    template <typename V> using second_tmpl = typename UGen::template type<T> ;
    using second_type = second_tmpl<type>;
};

template <typename T>
struct Template {
    using type = Template<T>;
};

struct TemplateGen {
    template <typename T> using type = Template<T>;
};

struct Derived : public Base<Derived, TemplateGen> {
};

// true
static_assert(std::is_same<Derived::second_type, Template<Derived> >::value, "false");
// false
static_assert(std::is_base_of<Base<Derived, TemplateGen>, Derived>::value, "false");

using Template2 = TemplateGen;

// false
static_assert(std::is_same<Base<Derived, TemplateGen>, Base<Derived, Template2>>::value, "false");

int main(){}
