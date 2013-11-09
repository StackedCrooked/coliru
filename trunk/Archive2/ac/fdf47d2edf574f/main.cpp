struct STRUCT
{
  STRUCT(int a){}
};

void func1(int& i){}
void func2(STRUCT& s){}
void func3(int i){}
void func4(STRUCT s){}

void main()
{
  //func1(int(56));  // ERROR: C2664
  func2(STRUCT(65)); // OK: anonymous object is created then assigned to a reference
  func3(int(46));    // OK: anonymous int is created then assigned to a parameter
  func4(STRUCT(12)); // OK: anonymous object is created then assigned to a parameter
}