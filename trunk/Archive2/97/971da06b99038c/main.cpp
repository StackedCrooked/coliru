enum { i = 1 };

class X {
  char v[i]; // error: i refers to ::i
             // but when reevaluated is X::i
  int f() { return sizeof(c); } // OK: X::c
  char c;
  enum { i = 2 };
};

int main()
{
}