#include <cstddef>

struct string {
private:
    const char* str;
    size_t len;
    
    constexpr unsigned equals(const string& other, unsigned i = 0) {
        return other.size() != len ? false : i == len ? true : str[i] == other[i] ? equals(other, i + 1) : false;
    }
public:
    template<size_t N>
    constexpr string(const char (&arr)[N]): str(arr), len(N) {}
    constexpr char operator[](size_t index) {
        return index < len ? str[index] : throw "error";
    }
    constexpr size_t size() {
        return len;
    }
    
    constexpr bool operator==(const string& other) {
        return equals(other);
    }
    
    constexpr bool operator!=(const string& other) {
        return !equals(other);
    }
};

int main() {
    constexpr string x = "Hello";
    constexpr string y = "Hello";
    static_assert(x == y, "...");
    static_assert(x[4] == 'o', "...");
    static_assert(x != "world", "...");
}