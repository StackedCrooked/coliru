struct S
{
  int x;
  void f() {
    auto l = [=, nullptr]{ x = 42; }; //this is implicitly captured here
    auto m = [=, true]{ x = 42; }; //this is implicitly captured here
  }
};
