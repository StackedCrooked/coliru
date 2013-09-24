#include <string>

namespace detail {
template<typename T>
struct defaulted_value {
    T b;
    constexpr defaulted_value() noexcept: b(0) {}
    explicit operator T() const noexcept {
        return b;
    }
};
} // detail

template<typename CharT, typename Traits = std::char_traits<CharT>>
struct basic_arg {
    std::basic_string<CharT, Traits> name;
    std::basic_string<CharT, Traits> description;
    detail::defaulted_value<CharT> short_name;
    detail::defaulted_value<bool> required;
};

using arg = basic_arg<char>;

int main() {
    arg x = {"Hello", "lol"};
}