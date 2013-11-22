class A {

};

class B {
  A m_a;
public:
  operator A () { return m_a; }
};

class C {
  B m_b;
public:
  operator A () { return m_b; }
};


void f(A a){}

int main()
{
  C c;
  f(c);
  return 0;
}