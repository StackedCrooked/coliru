struct S {
    bool b{};
    
    constexpr S() {
        static_assert(!b, "constructor");
    }
};

int main() {
    constexpr S s;
    static_assert(!s.b, "main");
}

