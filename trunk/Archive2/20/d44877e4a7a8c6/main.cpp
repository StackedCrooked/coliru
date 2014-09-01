struct M {
    M(int){}
    M() = delete;  // Allowing this would work.
};

struct B {
    B(int) {}
    B() = delete;
};

struct C : public B {
    using B::B;
    M n = {5};

    // C(int i) : B(i) {}  // Adding this would work
};

C c{1};

int main() {}
