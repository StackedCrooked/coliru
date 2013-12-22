int func () { static int * p = new int (); if (!p) return 1024; return *p; }

int main() {
  return func ();
}