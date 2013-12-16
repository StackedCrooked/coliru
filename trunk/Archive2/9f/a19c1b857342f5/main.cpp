#include <initializer_list>
#include <iostream>
#include <type_traits>
#include <valarray>

template<typename T>
void print(T seq) {
    for (const auto & elem: seq)
        std::cout << elem << " ";
    std::cout << std::endl;
}

// literal class
class conststr {
    const char * p;
    std::size_t sz;
 public:
    template<std::size_t N>
    constexpr conststr(const char(&a)[N]) : p(a), sz(N-1) {}
    // constexpr functions signal errors by throwing exceptions from operator ?:
    constexpr char operator[](std::size_t n) const {
        return n < sz ? p[n] : throw std::out_of_range("");
    }
    constexpr std::size_t size() const { return sz; }
};

template<int N> 
struct print_stuff_as_warning {
    char operator()() {
        return N + 256;//deliberately causing overflow
    }
};

constexpr bool palindrom(conststr phrase, size_t offset = 0) {
    return (offset > phrase.size() - offset -1) ?
        true
        : (phrase[offset] != phrase[phrase.size() - offset -1]) ?
            false
            : palindrom(phrase, offset + 1);
}

template<bool x>
void constexpr_eval() {}

int main() {
    constexpr_eval<palindrom("testset")>;
    std::valarray<int> a = {'a', 'b', 'c', 0};
    using T = decltype(a);
    print(a);
    a = {2, 3};
    print(a);
    a = (decltype(a){4, 5});
    print(a);
    a = T{4, 5};
    print(a);
    a = a + a;
    print(a);
    a = a + T{4, 5};
    print(a);
    a = a + decltype(a){4, 5};
    print(a);
    a = T{4, 5} + a;
    print(a);
    std::initializer_list<int> i({4, 5});
    a = T(i) + a;
    print(a);
}
