template<class... Ts, int... Ns> void foo() {}

int main() {
    foo<int, double, 1, 2, 3>();
}
