template <typename T>
struct A {
  typedef int X;
  X f(X);
};

template <typename T>
auto A<T>::f(A<T>::X) -> A<T>::X
{
    A<T>::X i;
    return i;
}

int main()
{    
}
