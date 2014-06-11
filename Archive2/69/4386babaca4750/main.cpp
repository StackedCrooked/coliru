struct A
{};

struct B
{
   operator int() { return 42; }
};

int main()
{
   A a;
   const int x = a;  // error: no conversion from `A` to `int`
   
   B b;
   const int y = b;  // OK
}