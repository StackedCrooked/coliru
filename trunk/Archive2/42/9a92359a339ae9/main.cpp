#include <iostream>
#include <typeinfo>

template<class T>
void print_type(T)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    std::cout << typeid(T).name() << std::endl;
}

template<class T>
struct opaque {};

template<class T>
opaque<T> make_opaque(T)
{
    return {};
}

template<class RHS>
void operator_assign(RHS)
{
    print_type(make_opaque([]{}));
}

struct the_long_template_type_you_want_to_hide {};

int main(int argc, char** argv) {
    operator_assign(the_long_template_type_you_want_to_hide());
    return 0;
}