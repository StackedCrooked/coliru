#include <iostream> 

struct base
{
    enum type { BASE, A, B, C, D };
    type struct_type = BASE ;
    // ...
};

template < base::type TYPE > struct type : base { type() { struct_type = TYPE ; } };

struct derived_A : type<base::A> { /* ... */ };
struct derived_B : type<base::B> { /* ... */ };
struct derived_C : type<base::C> { /* ... */ };

int main()
{
    derived_A a ; std::cout << a.struct_type << '\n' ; // 1
    derived_B b ; std::cout << b.struct_type << '\n' ; // 2
    derived_C c ; std::cout << c.struct_type << '\n' ; // 3
}
