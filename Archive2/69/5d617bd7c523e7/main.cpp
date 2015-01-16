struct A {
    void test() const&& {}
    void test() const& = delete;
    void test() & = delete;
    void test() && = delete;
};

const A foo() { return {}; }

int main() { foo().test(); }
