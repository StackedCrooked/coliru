struct A
{
    A(int) {} // converting constructor
    A(int, int) {} // converting constructor (C++11)
    operator int() const { return 0; }
};
 
struct B
{
    explicit B(int) {}
    explicit B(int, int) {}
    explicit operator int() const { return 0; }
};
 
int main()
{
    A a1 = 1; // OK: copy-initialization selects A::A(int)
    A a2(2); // OK: direct-initialization selects A::A(int)
    A a3 {4,5}; // OK: direct-list-initialization selects A::A(int, int)
    A a4 = {4,5}; // OK: copy-list-initialization selects A::A(int, int)
    int na1 = a1; // OK: copy-initialization selects A::operator int()
    int na2 = static_cast<int>(a1); // OK: static_cast performs direct-initialization
    A a5 = (A)1; // OK: explicit cast performs static_cast
 
//  B b1 = 1; // Error: copy-initialization does not consider B::B(int)
    B b2(2); // OK: direct-initialization selects B::B(int)
    B b3 {4,5}; // OK: direct-list-initialization selects B::B(int, int)
//  B b4 = {4,5}; // Error: copy-list-initialization does not consider B::B(int,int)
//  int nb1 = b2; // Error: copy-initialization does not consider B::operator int()
    int nb2 = static_cast<int>(b2); // OK: static_cast performs direct-initialization
    B b5 = (B)1; // OK: explicit cast performs static_cast
}