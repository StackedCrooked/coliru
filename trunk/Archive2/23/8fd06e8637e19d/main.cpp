struct A {
    void f() const {
        g(); // enforced semantic error
    }
    void g() {}
};

/*
    void f() noexcept {
        g(); // enforced semantic error
    }
    void g() { throw "something"; }
*/


int main(int argc, char** argv) {
    return 0;
}