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

void b::member_of_b() { ++protected_member ; } // fine: member of b can access inherited protected member in b

void bar( b& object ) { ++object.protected_member ; } // fine: friend of b can access inherited protected member in b

struct e ;

struct c : b
{
    friend void baz( c& object ) ;
    friend void baz( b& object ) ;
    friend void baz( e& object ) ;
    
    struct d 
    { 
        static void member_of_d( c& object );
        static void member_of_d( b& object );
    };
};

struct e : c {};

void baz( c& object ) { ++object.protected_member ; } // fine: friend of c can access inherited protected member in c

// void baz( b& object ) { ++object.protected_member ; } // *** error: can't access inherited protected member of a in b

void baz( e& object ) { ++object.protected_member ; } // fine: friend of c can access inherited protected member in c (e is derived from c)

void c::d::member_of_d( c& object ) { ++object.protected_member ; } // fine: member of member of c can access inherited protected member in c

// void c::d::member_of_d( b& object ) { ++object.protected_member ; } // *** error: can't access inherited protected member of a in b

int main()
{
    a a ; a.member_of_a() ; foo(a) ;

    c b ; b.member_of_b() ; bar(b) ;

    c c ; c::d::member_of_d(c) ;
}
