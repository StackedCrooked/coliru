template <typename T>
struct A {
  typedef int X;
  X f();
};

template <typename T>
A<T>::X f()
{
}
