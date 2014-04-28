struct A {
  int b;
} ;

struct A foo() {
  return (struct A) {  42 };
}

int main()
{
}