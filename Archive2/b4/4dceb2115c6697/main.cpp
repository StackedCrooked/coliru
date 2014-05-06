struct type0 {};
struct type1 {};
 
struct base0 { int operator()(type0) const { return 1; } };
struct base1 { double operator()(type1) const { return 1.1; } };
 
struct test_object_ : base0,base1 {};
struct test_object : test_object_
{
  int operator()(type0) const { return 5; }
  double operator()(type1) const { return 42.666; }
};
 
int main()
{
  test_object o;
  test_object_ op;
 
  int x = o(type0());  // 1
  int y = op(type0()); // 2
} 