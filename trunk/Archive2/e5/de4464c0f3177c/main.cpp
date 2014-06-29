class Test{
public:
  void foo(bool flag);
};

void Test::foo(bool flag = true ){
  // ...
}

int main()
{
    Test o;
    o.foo();
}