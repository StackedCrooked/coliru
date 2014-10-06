template<typename = void>
struct foo;

template<>
struct foo<void> {
    // impl
};

int main() {
}