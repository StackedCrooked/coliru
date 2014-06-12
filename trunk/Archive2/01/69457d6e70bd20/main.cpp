namespace N {

    struct C {
        friend int f(const C& c) {
            return 1;
        }
        friend int g(const C& c) {
            return 2;
        }
    };

    int f(const C& c);
    int g(const C& c);

    struct D {
        void f() {
            g(C{});
            ::N::f(C{});
        }
    };
}

int main() {}
