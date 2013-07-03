class Foo {
public:
    ~Foo() = delete;
};

int main() {
    auto foo = new Foo();
    return 0;
}
