template <typename T> class A {
public:
  class B;
  template <typename U> class C;
};

template <typename T>
class A<T>::B {
public:
  template <typename U> static void Create();
};

template <typename T> template <typename U>
class A<T>::C {
private:
  C() = default;

  friend void B::Create<U>();
};

template <typename T> template <typename U>
void A<T>::B::Create() {
  C<U>{};
}

int main() {
  A<int>::B::Create<char>();
}