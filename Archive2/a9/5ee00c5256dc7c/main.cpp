    #include <iostream>
    
    #define override

class A {
public:
  virtual void do();
};

class B1 : public virtual A {
public:
  override void do();
};

class B2 : public virtual A {
public:
  override void do();
};

class C : public B1, public B2 {};

int main(int argc, char** argv) {
  C* el = new C();
  el->do(); /* WHAT HAPPENS? */
}