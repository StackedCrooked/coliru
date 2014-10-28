template<typename T>
void f() {
    unsigned i = 0;
    int x = 10;
    if(x > i) {}
}

struct test {
    int stuff;
};

int main() {
    f<decltype(test::stuff)>();
}