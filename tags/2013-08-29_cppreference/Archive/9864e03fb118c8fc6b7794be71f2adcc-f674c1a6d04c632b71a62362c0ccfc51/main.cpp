#include <iostream>
#include <string>
#include <type_traits>
#include <assert.h>

#define ENUM_FLAG_UNARY_OPERATOR(OP)                                                                        \
    template <typename Enum,                                                                                \
              typename = typename std::enable_if<std::is_enum<Enum>::value && is_flag<Enum>::value>::type   \
             >                                                                                              \
    Enum operator OP(Enum value) {                                                                          \
        return static_cast<Enum>(OP to_underlying(value));                                                  \
    }

#define ENUM_FLAG_BINARY_OPERATOR(OP)                                                                       \
    template <typename Enum,                                                                                \
              typename = typename std::enable_if<std::is_enum<Enum>::value && is_flag<Enum>::value>::type   \
             >                                                                                              \
    Enum operator OP(Enum const& l, Enum const& r) {                                                        \
        return static_cast<Enum>(to_underlying(l) OP to_underlying(r));                                     \
    }                                                                                                       \
                                                                                                            \
    template <typename Enum,                                                                                \
              typename = typename std::enable_if<std::is_enum<Enum>::value && is_flag<Enum>::value>::type   \
             >                                                                                              \
    Enum operator OP##= (Enum& l, Enum const& r) {                                                          \
        return l = l OP r;                                                                                  \
    }

namespace enums {
    template <bool B>
    struct Bool : std::integral_constant<bool, B> {};

    typedef Bool<true> True;
    typedef Bool<false> False;

    template <typename T>
    struct is_flag : False {};

    template <
        typename Enum,
        typename = typename std::enable_if<std::is_enum<Enum>::value>::type,
        typename Underlying = typename std::underlying_type<Enum>::type
    >
    Underlying to_underlying(Enum value) {
        return static_cast<Underlying>(value);
    }

    ////bleh
    //template <typename T>
    //struct is_enum_class {
    //    static const bool value = std::is_enum<T>::value
    //        && !std::is_convertible<T, std::underlying_type<T>::type>::value;
    //};


    namespace operators {
        ENUM_FLAG_UNARY_OPERATOR(~)
        ENUM_FLAG_BINARY_OPERATOR(&)
        ENUM_FLAG_BINARY_OPERATOR(|)
        ENUM_FLAG_BINARY_OPERATOR(^)
    }
}

#undef ENUM_FLAG_UNARY_OPERATOR
#undef ENUM_FLAG_BINARY_OPERATOR

enum class MyFlag : uint32_t
{
    a = 1 << 0,
    b = 1 << 1,
    c = 1 << 2,
};

enum class SomeCrap
{
    lel,
    idk,
};


namespace enums {
    template<> struct is_flag<MyFlag> : True {};
}

int main()
{
    using namespace enums::operators;
    MyFlag m = MyFlag::a | MyFlag::c;
    SomeCrap s = SomeCrap::lel | SomeCrap::idk;
}
