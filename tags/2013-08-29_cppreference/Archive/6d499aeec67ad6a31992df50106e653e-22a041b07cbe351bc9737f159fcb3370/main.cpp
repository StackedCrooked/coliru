struct A {
  int a;
};

struct B : A {

};

A a;

int g(B *b) {
   a.a = 10;
   b->a++;
   return a.a;
}