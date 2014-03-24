void f() { }
auto x = []{};

struct Lambda : decltype(x) {
    constexpr operator decltype(f)*() {
        return f;   
    }
};

extern Lambda lambda;

int main() {
    decltype(f) * cfunction = lambda;
}