#include <string>
#include <locale>
#include <new>

template<typename From, typename To>
struct widen {
private:
    std::locale loc;
    const std::ctype<To>* t;
public:
    widen(const std::locale& loc = std::locale{}) noexcept: loc(loc), t(&std::use_facet<std::ctype<To>>(loc)) {}

    std::basic_string<To> operator()(const std::basic_string<From>& str) const noexcept {
        const From* ptr = str.c_str();
        To* buffer = new(std::nothrow) To[str.size()];
        if(buffer == nullptr)
            return {};
        t->widen(ptr, ptr + str.size(), buffer);
        return { buffer, str.size() };
    }
};

template<typename T>
struct widen<T, T> {
    widen() noexcept = default;
    std::basic_string<T>& operator()(const std::basic_string<T>& str) const noexcept {
        return str;
    }
};

#include <iostream>

int main() {
    std::wcout << widen<char, wchar_t>{}("Hello");
}