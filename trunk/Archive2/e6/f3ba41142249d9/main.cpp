void foo(double val) { cout << "double\n";}

class obj {
public:
  using ::foo; // (1) compile error: using-declaration for non-member at class scope
  void callFoo() { 
    using ::foo; // (2）will cause the global version always be called
    foo(6.4); 
    foo(0); 
  }
private:
  void foo(int val) {cout << "class member foo\n"; }
};