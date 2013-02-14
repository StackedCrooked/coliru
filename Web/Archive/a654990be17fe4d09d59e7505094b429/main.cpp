#include <type_traits>

template<typename SubType>
struct Enum {};

template<typename Subtype>
struct Enumerator
{
    using enum_type = Enum<Subtype>;
};

template<typename EnumType>
struct Begin : Enumerator<EnumType>
{
};

template<typename EnumType>
struct End : Enumerator<EnumType>
{
};

template<typename Subtype>
constexpr End<Subtype> end(const Enum<Subtype> & enum_) { return End<Subtype>{}; }


struct RGB   : Enum<RGB> {};

struct Red   : Begin<RGB>  {};
struct Green : Enumerator<RGB>  {};
struct Blue  : Enumerator<RGB>  {};


constexpr Green    next(Red  ) { return Green{}; }
constexpr Blue     next(Green) { return Blue{}; }
constexpr End<RGB> next(Blue ) { return End<RGB>{}; }


