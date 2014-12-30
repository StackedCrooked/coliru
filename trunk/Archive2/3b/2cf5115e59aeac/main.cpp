struct a {
    void b();
};

struct b {};

struct d : a, b {
    using typename b::b;
    
    void f() {
        b q;
    }
};

int main() {}