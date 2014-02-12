struct X {};

constexpr auto x = X{};

struct S {
    static constexpr auto& rx = x;  
};

int main() {}