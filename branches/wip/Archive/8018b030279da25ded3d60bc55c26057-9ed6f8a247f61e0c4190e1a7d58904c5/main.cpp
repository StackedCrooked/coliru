struct A {
  A(int = 0) {}
};

int i;
int* p = &i;

int main () {
  (A(*p));
  p = 0;
}
