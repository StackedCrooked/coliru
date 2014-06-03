template<typename T>
struct test {
    using type = T;
    using other = const T&;
};

struct my_test : test<int> {
    type x() {
        return 10;
    }
};

int main() {}