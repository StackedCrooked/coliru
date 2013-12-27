#include <iostream>
#include <functional>
#include <queue>
#include <string>

struct command
{
    template < typename CALLABLE, typename... ARGS >
    void add( CALLABLE&& fn, ARGS&&... args )
    { tasks.emplace( std::bind( fn, std::forward<ARGS>(args)... ) ) ; }

    void operator() ()
    {
        while( !tasks.empty() )
        {
            tasks.front()() ;
            tasks.pop() ;
        }
    }

    private: std::queue< std::function< void() > > tasks ;
};

int main()
{
    struct A
    {
        int foo() const { std::cout << "A::command(int) const\n" ; return 0 ; }
        void bar( int, int ) const { std::cout << "A::bar(int,int)\n" ; }
        double baz( int& a, int b, float c, long d )
        { std::cout << "A::baz(int,int,float,long)\n" ; return v += a += b+c+d ; }

        static void commandbar( int, double )
        { std::cout << "static void A::commandbar( int, double )\n" ; }

        double v = 5.6 ;
    };

    command cmd ;
    A a ;

    cmd.add( &A::foo, a ) ;
    cmd.add( &A::bar, std::ref(a), 12, 345 ) ;

    int i = 12 ;
    cmd.add( &A::baz, std::addressof(a), std::ref(i), 345, 6.74, 8 ) ;

    cmd.add( []( A, const char*) { std::cout << "closure\n" ; }, a, "hello" ) ;

    std::string str ;
    cmd.add( &std::string::reserve, std::ref(str), 1024*1024 ) ;

    std::cout << "*** execute command ***\n" ;
    cmd() ;
    std::cout << "\ni == " << i << "  a.v == " << a.v
               << "\nstr.capacity() == " << str.capacity() << '\n' ;
}
