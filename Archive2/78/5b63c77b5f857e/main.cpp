template<typename T>
class B { };

namespace N {
    class A {

    };

    template<typename T>
    void foo(B<T>) { }
}

int main() {
    foo(B<N::A>());
}
