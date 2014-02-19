#include <iostream>

struct A
{
    static A& instance() ;

    int i = 7 ;

    private:
        A() { std::cout << "A::constructor\n" ; }
        ~A() { std::cout << "A::destructor\n" ; }
        A( const A& ) = delete ;
        A( A&& ) = delete ;
};

A& A::instance()
{
    static A singleton ; // Meyers' singleton
    return singleton ;
}

struct B
{
   B() { std::cout << "B::constructor\n" ; }

   ~B()
   {
       std::cout << "B::destructor tries to access A::instance\n" ;
       A& a = A::instance() ;

       ++a.i ; // use a
   }
};

B b ; // B is constructed

int g = A::instance().i ; // Myers' singleton is constructed

// destructor of objects with static storage duration is in
// reverse order of constructon
// since the Myers' singleton was constructed after b,
// it would be destroyed before destructor of b executes
// and the destructor of b would get a dead eference

int main()
{
}
