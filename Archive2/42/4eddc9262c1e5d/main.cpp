struct M {
    friend void f() {}
    M() {
        f();
    }
};

int main() {
    M m;
}
