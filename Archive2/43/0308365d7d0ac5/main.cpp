namespace N {
    class A;
}
using namespace N;

class B {
    int i;
    friend A;
};

namespace N {
    class A {
        B m;
        int get() { return m.i; }
    };
}

int main() {}