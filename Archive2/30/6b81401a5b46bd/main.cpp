struct a {
    void b();
};

struct b {};

struct d : a, b {
    using typename b::b;
};

int main() {
    d q;
}