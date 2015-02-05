#include <iostream>
#include <sstream>

class Color {
    std::uint8_t r;
    std::uint8_t g;
    std::uint8_t b;
    std::uint8_t a;

public:
    constexpr Color(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a = 255)
        : r{r}, g{g}, b{b}, a{a} {}

    std::string as_str()
    {
        std::stringstream ss;
        ss << (int) r << "," << (int) g << "," << (int) b << "," << (int) a;
        return ss.str();
    }
};

std::ostream& operator<<(std::ostream& os, Color c)
{
    os << c.as_str();
    return os;
}

constexpr bool is_numeric(const char c)
{
    return (c >= '0' && c <= '9') ||
        (c >= 'a' && c <= 'f') ||
        (c >= 'A' && c <= 'F');
}

constexpr std::uint8_t numeric_value(const char c)
{
    return c >= '0' && c <= '9' ? c - '0' :
        c >= 'a' && c <= 'f' ? c - 'a' + 10 :
        c >= 'A' && c <= 'F' ? c - 'A' : 0;
}

constexpr std::uint8_t numeric_value_2(char c1, char c2)
{
    return numeric_value(c1) * 16 + numeric_value(c2);
}

template <unsigned len, std::uint8_t ALPHA, std::uint8_t RED, std::uint8_t GREEN,
          std::uint8_t BLUE>
constexpr Color build_color_literal()
{
    return Color{RED, GREEN, BLUE, ALPHA};
}

template <unsigned len, std::uint8_t ALPHA, std::uint8_t RED, std::uint8_t GREEN,
          std::uint8_t BLUE, char DIGIT1, char DIGIT2, char... REST>
constexpr Color build_color_literal()
{
    return
        len == 2 ? build_color_literal<0, ALPHA, RED, GREEN, numeric_value_2(DIGIT1, DIGIT2), REST...>() :
        len == 4 ? build_color_literal<2, ALPHA, RED, numeric_value_2(DIGIT1, DIGIT2), BLUE, REST...>() :
        build_color_literal<4, ALPHA, numeric_value_2(DIGIT1, DIGIT2), GREEN, BLUE, REST...>();
}

template <char ZERO, char X, char DIGIT1, char DIGIT2, char... REST>
constexpr Color build_alpha_literal()
{
    static_assert(ZERO == '0' && X == 'x', "Not a hex number!");
    return build_color_literal<6, numeric_value_2(DIGIT1, DIGIT2), 0, 0, 0, REST...>();
}

template <char ZERO, char X, char... REST>
constexpr Color strip_color_digits()
{
    static_assert(ZERO == '0' && X == 'x', "Not a hex number!");
    return build_color_literal<6, 255, 0, 0, 0, REST...>();
}

template <char... STR>
constexpr typename std::enable_if<sizeof...(STR) == 8, Color>::type operator""_c()
{
    return strip_color_digits<STR...>();
}

template <char... STR>
constexpr typename std::enable_if<sizeof...(STR) == 10, Color>::type operator""_c()
{
    return build_alpha_literal<STR...>();
}

int main()
{
    std::cout << 0x131415_c << std::endl;
    std::cout << 0xff131415_c << std::endl;
}
