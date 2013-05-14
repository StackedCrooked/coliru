
struct Base1 {};
struct Base2 {};
struct base_3 {};


struct A : Base1, Base2 {};

int main()
{
    A a;
    Base1& base1 = a;
    
    static_cast<Base2&>(static_cast<A&>(base1));
}