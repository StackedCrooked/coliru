template <int N>
struct Foo {};

int main()
{
  Foo<static_cast<int>(100 >> 1)> x;
}
