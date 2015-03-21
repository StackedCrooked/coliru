struct a
{
    void member_of_a() ;

    protected: int protected_member = 0 ;

    friend void foo( a& object ) ;
};

void a::member_of_a() { ++protected_member ; } // fine: member of a

void foo( a& object ) { ++object.protected_member ; } // fine: friend of a

struct b : a
{
    void member_of_b() ;

    friend void bar( b& object ) ;
};

void b::member_of_b() { ++protected_member ; } // fine: member of b

void bar( b& object ) { ++object.protected_member ; } // fine: friend of b

struct c : b
{
    struct d 
    { 
        static void member_of_c( c& object ) { ++object.protected_member ; } // fine: can access protected member of c
        // static void member_of_c( b& object ) { ++object.protected_member ; } // *** error: can't access protected member of a
    };
};

int main()
{
    a a ; a.member_of_a() ; foo(a) ;

    c b ; b.member_of_b() ; bar(b) ;

    c c ; c::d::member_of_c(c) ;
}
