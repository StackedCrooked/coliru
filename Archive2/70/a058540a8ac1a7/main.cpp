struct S1 {
  S1(int i) {}
};

struct S2 {
  S2(const S1&) {}
};

void fn1(const S1& s1) {}
void fn2(const S2& s2) {}

int main()
{
  fn1(1);
  fn2(S1(1));
  fn2(1);
}