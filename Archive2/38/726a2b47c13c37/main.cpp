struct base {
  virtual void foo(int) {}
  virtual void foo(char) {}
};

struct derived : public base {
  void foo(int) override {}    
};

int main(void) {
}
