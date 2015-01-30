class Bar
{
public:
   void Foo(bool = false, int = 10, int = 20) {}
};

int main()
{
   int x = 40, y = 50;
   Bar b;
   b.Foo();            // correct usage
   b.Foo(true, x, y);  // correct usage
   b.Foo(x, y);        // problem:  compiles but won't do what the caller expects
}