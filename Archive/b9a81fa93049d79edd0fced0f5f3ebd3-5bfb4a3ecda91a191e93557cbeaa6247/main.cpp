namespace A
{
    inline namespace en {
        enum a { One = 1, Two = 2 };
    }
    
    enum c {Three};
}

namespace B
{
    using namespace A::en;
    using b = A::a;
}

A::a a_value = A::One; // works
B::b b_value = B::One; // works
B::b c_value = A::One; // works
A::c meh = B::Three; //fails because only en was brought into B

int main ()
{
   return 0;
}