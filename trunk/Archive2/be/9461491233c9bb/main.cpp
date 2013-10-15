#include <stdexcept>

class string {
private:
    const char* const data;
    size_t len;
public:
    template<size_t N>
    constexpr string(const char (&arr)[N]) noexcept: data(arr), len(N - 1) {}
    
    constexpr char operator[](size_t n) const {
        return n < len ? data[n] : throw std::out_of_range("");
    }
    
    constexpr size_t size() const noexcept {
        return len;
    }
};

int main() {
    constexpr string hello = "Hello World";
    static_assert(hello.size() == 11, "error");
    static_assert(hello[0] == 'H', "error");
}