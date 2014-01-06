template <typename T>
class MyClass
{
public:
  typedef int my_int;

  const my_int foo();

};

template <typename T>
const auto MyClass<T>::foo() -> my_int
// auto MyClass<T>::foo() -> const my_int // THIS WORKS!
{
  return my_int(1);
}

int main()
{
  MyClass<int> m;
  m.foo();
}