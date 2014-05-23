template <typename, typename> struct A {};

struct B {
    const A a = A<int, int>{};
};

int main() {}
