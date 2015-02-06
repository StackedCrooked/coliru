 struct S;
  template<void (*)(S, S)> struct X {};
  void operator>(S, S);
  X<operator> > x;
  
int main(){}