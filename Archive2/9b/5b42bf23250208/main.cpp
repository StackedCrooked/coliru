#include <stdexcept>
#include <vector>

struct A {
    void f() const {
        g(); // enforced semantic error
    }
    void g() {}
};



int main(int argc, char** argv) {
    return 0;
}