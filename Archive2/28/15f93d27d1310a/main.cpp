#include <cstdio>
#include <cstdarg>
#include <iostream>
#include <tuple>

#ifdef __GNUC__
#define PRINTF_FORMAT(x,y) __attribute__((format(printf,x,y)))
#else
#define PRINTF_FORMAT(x,y)
#endif

class OutStream {
public:
    OutStream& operator<<(const char* s);
    OutStream& operator<<(int n);
    OutStream& operator<<(unsigned int n);
    // ...
    OutStream& vformat(const char* fmt, va_list args);
    OutStream& format(const char* fmt, ...) PRINTF_FORMAT(2,3);
};

OutStream& OutStream::operator << (const char* s) {
    std::cout << s;
    return *this;
}

OutStream& OutStream::operator << (int n) {
    std::cout << n;
    return *this;
}

OutStream& OutStream::vformat(const char* fmt, va_list args) {
    std::vprintf(fmt, args);
    return *this;
}

OutStream& OutStream::format(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vformat(fmt, args);
    va_end(args);
    return *this;
}

template <typename...Ts>
class formatter {
    const char* fmt_;
    std::tuple<Ts...> args_;

    template <std::size_t...Is>
    void expand(OutStream& os, std::index_sequence<Is...>) && {
        os.format(fmt_, std::get<Is>(std::move(args_))...);
    }

public:
    template <typename...Args>
    formatter(const char* fmt, Args&&...args) :
        fmt_{fmt}, args_{std::forward<Args>(args)...} {}

    friend OutStream& operator << (OutStream& os, formatter&& f) {
        std::move(f).expand(os, std::index_sequence_for<Ts...>{});
        return os;
    }
};
    
template <typename...Args>
formatter<Args&&...> format(const char* fmt, Args&&...args) {
    return {fmt, std::forward<Args>(args)...};
}

int main() {
    OutStream out;
    out << 1 << format(" formatted %04X ", 2) << "3\n";
}
