
struct A {
    auto self_() -> decltype(*this) { return this; }
    using self = decltype(((self_*)0)());
};

int main() {
    A::self x;
}