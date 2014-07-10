class A {
  public:
  virtual void test() = 0;
};

class B : public A {
    void test() {}
};

int main() {

 A t = new A();
 return 0;
}