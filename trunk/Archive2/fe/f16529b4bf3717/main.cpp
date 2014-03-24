template<typename T>
struct S {
    S() = default;
    S(const S &) = default;
};

int main() {
    S<int> s;
    auto s2 = s;
}