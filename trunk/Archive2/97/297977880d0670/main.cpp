#include <iostream>

struct S {
  void fn() { sfn(); }
private:
  static void sfn() { std::cout << "oh hai\n"; }
};

int main()
{
    S s;
    s.fn();
    //s.sfn();
}