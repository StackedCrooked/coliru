template<int>
class baz {
public:
    void bar(baz<0> that) {
        that.foo();
    }
    constexpr int foo() const {
        return 0;
    }
};

int main() {
}
