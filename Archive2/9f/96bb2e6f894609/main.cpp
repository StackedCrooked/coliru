struct init {
    init(long    long   v) : t(type::longlong), x(v) {}
    init(char    const* v) : t(type::pcsz),     s(v) {}
    init(wchar_t const* v) : t(type::pwcsz),    w(v) {}

    init() = default;

    enum class type { longlong, pcsz, pwcsz } t;
    union { long long x; char const* s; wchar_t const* w; };
};

#include <iostream>

static inline std::ostream& operator<<(std::ostream& os, init::type t) {
    switch (t) {
        case init::type::longlong: return os << "long long";
        case init::type::pcsz:     return os << "char const*";
        case init::type::pwcsz:    return os << "wchar_t const*";
        default:                   return os << "?";
    }
}

static inline std::ostream& operator<<(std::ostream& os, init const& v) {
    switch (v.t) {
        case init::type::longlong: return os << v.x;
        case init::type::pcsz:     return os << v.s;
        case init::type::pwcsz:    return os << v.w;
        default:                   throw std::runtime_error("bad type discriminator");
    }
}

int main() {
    init initial_data [] = {
        3 ,      // initializes x, brace elision
        "foo" ,  // initializes s 
        L"Foo"   // initializes w
    };

    for(auto& v : initial_data)
        std::cout << v.t << "\t" << v << "\n";
}
