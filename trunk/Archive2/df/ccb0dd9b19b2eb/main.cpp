struct B { void f(); };
struct D : B {};
template<typename T, typename R> void g(R T::*);

int main() {
    g<D>(&D::f);
}