    #include <iostream>
    
    #define override

class A {
public:
  virtual void foo();
};

class B1 : public virtual A {
public:
  override void foo();
};

class B2 : public virtual A {
public:
  override void foo();
};

class C : public B1, public B2 {};

int main(int argc, char** argv) {
  C* el = new C();
  el->foo(); /* WHAT HAPPENS? */
}