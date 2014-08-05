class Base {
protected:
  void foo() {}
};

struct Derived : public Base {
  friend void Base::foo();
};
  
int main() {
 
}