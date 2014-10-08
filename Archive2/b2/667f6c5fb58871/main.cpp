struct A { };
namespace N {
  struct A {
    void g() { }
    template <class T> operator T();
  };
}
int main() {
   N::A a;
   a.operator A();
}
