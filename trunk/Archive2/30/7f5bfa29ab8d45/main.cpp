template< typename > struct X
{
  void foo() {}

  auto bar() -> decltype( X::foo() )
  {
    return foo();
  }
};

int main()
{
  X<int>().bar();
}
