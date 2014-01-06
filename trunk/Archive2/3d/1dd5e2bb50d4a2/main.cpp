#include <type_traits>
#include <stdexcept>
#include <cstddef>

struct string {
private:
    const char* str;
    size_t len;
    
    constexpr bool less(const char* l, const char* r) {
        return *l && (*l < *r) && less(l + 1, r + 1);
    }
    
    constexpr bool equal(char const* l, char const* r) {
      return (*l && *r) ? (*l == *r && equal(l + 1, r + 1)) : (!*l && !*r);
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
        return len != other.size() ? false : equal(str, other.str);
    }
    
    constexpr bool operator!=(const string& other) {
        return !(*this == other);
    }
    
    constexpr bool operator<(const string& other) {
        return less(str, other.str);
    }
    
    constexpr bool operator>(const string& other) {
        return less(other.str, str);
    }
    
    constexpr bool operator<=(const string& other) {
        return !(other < *this);
    }
    
    constexpr bool operator>=(const string& other) {
        return !(*this < other);
    }
};

int main() {
    constexpr string x = "Hello";
    constexpr string y = "Hello";
    static_assert(x == y, "...");
    static_assert(x <= y, "...");
    static_assert(x[4] == 'o', "...");
    static_assert(x != "world", "...");
}