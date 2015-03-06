struct A {
    A(int i = 42) : i(i) {} // default constructor, yes
    int i;
};

int main() {
    A a3{};
}