struct A {
    void f() const {
        g(); // enforced semantic error
    }
    void g() {}
};

/*
struct A {
    void f() {
        g(); // enforced semantic error
    }
    void g() except { throw "something"; }
};
*/


int main(int argc, char** argv) {
    return 0;
}