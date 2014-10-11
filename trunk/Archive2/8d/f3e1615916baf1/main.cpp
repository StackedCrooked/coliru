struct X {
    explicit X(int, int) {}
};

void func(X) {}

int main() {
    func({1, 2});
}