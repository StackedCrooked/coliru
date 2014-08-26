template<unsigned N>
  struct C { };

template <unsigned N>
void foo(C<N>, const int (& /*x*/)[N]) {}

int main()
{
  foo(C<4>(), {1,2,3});
  return 0;
}