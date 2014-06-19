#include <cstddef>

constexpr bool IsDigit(const char C) {
    return '0' <= C && C <= '9';
}

struct StringView {
    template<std::size_t N>
    constexpr StringView(const char(&S)[N]) : Str_{S}, Size_{N - 1} {}
    
    constexpr bool IsNumber(std::size_t I = 0) const {
        return 
            I == Size_ ? true :
            !IsDigit(Str_[I]) ? false :
            IsNumber(I + 1)
        ;
    }
private:
    const char *Str_;
    const std::size_t Size_;
};

int main() {
    constexpr StringView sv{"123456"};
    static_assert(sv.IsNumber(), "sv isn't a number? WTF?");
    
    constexpr StringView sv2{"123a456"};
    static_assert(!sv2.IsNumber(), "sv2 is a number? WTF?");
}