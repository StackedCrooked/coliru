
struct Foo {
  void fn();
  
};


int main()
{
    Foo f;
    using fn_t = decltype(f.fn());
}