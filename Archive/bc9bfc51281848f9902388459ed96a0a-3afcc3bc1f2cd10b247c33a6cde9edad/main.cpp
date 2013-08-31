#include <type_traits>

int main() {
    static_assert(std::is_same<decltype("abc"), const char[4]>::value, "#1");
    static_assert(std::is_same<decltype("abc"), const char(&)[4]>::value, "#1");
}