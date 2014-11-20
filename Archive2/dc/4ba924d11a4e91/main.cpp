struct test {};

struct tester {
    ::test test() { return {}; }
    void test(::test) {}
};

int main() {}