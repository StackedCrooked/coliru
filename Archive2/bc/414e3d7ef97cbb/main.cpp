template<class T> struct id{ using type = T; };
template<class T>
using id_t = typename id<T>::type;

struct B { void f(){} };
struct D : B {};
template<typename T, typename R> void g(R id_t<T>::*){}

int main() {
    g<D, void()>(&D::f);
}