struct A
{
    A(int) {}
    operator int() const { return 0; }
};
 
struct B
{
    explicit B(int) {}
    explicit operator int() const { return 0; }
};
 
int main()
{
    // A has no explicit ctor / conversion, everything is fine
    A a1 = 1;
    A a2 ( 2 );
    A a3 { 3 };
    int na1 = a1;
    int na2 = static_cast<int>( a1 );
 
    //B b1 = 1; // Error: implicit conversion from int to B
    B b2 ( 2 ); // OK: explicit constructor call
    B b3 { 3 }; // OK: explicit constructor call
    //int nb1 = b2; // Error: implicit conversion from B to int
    int nb2 = static_cast<int>( b2 ); // OK: explicit cast
}