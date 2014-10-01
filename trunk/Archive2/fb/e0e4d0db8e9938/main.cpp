#include <iostream>
#include <functional>
#include <vector>
#include <string>

struct button /* button_base */
{
    const int id ;
    static int next_id ;

    button() : id(next_id++) {}

    template < typename CALLABLE, typename... ARGS >
    explicit button( int id, CALLABLE&& fn, ARGS&&... args ) : id(id)
    { 
        if( id > next_id ) next_id = id + 1 ; 
        subscribe( std::forward<CALLABLE>(fn), std::forward<ARGS>(args)... ) ;
    }

    template < typename CALLABLE, typename... ARGS >
    void subscribe( CALLABLE&& fn, ARGS&&... args )
    { commands.emplace_back( std::bind( std::forward<CALLABLE>(fn), std::forward<ARGS>(args)... ) ) ; }

    /* virtual */ void click()
    {
        std::cout << "*** button::click: button #" << id << " is clicked.\n" ;
        for( const auto& cmd : commands ) cmd() ;
    }

    std::vector< std::function< void() > > commands ;
};

int button::next_id = 1 ;

void foo( int i ) { std::cout << "::foo( " << i << " )\n" ; }

int bar( std::string tag, std::string info  )
{
    std::cout << "::bar( '" << tag << "', '" << info << "' )\n" ;
    static int call_cnt = 0 ;
    return ++call_cnt ;
}

int main()
{
    struct A
    {
        void mfun( double d ) const
        { std::cout << "A::mfun( " << this << ", " << d << " )\n" ; }
    } a;

    button my_buttons[] =
    {
        button( 19, foo, 19 ),
        button( 26, bar, "from button twentysix", "hello" ),
        button( 15, &A::mfun, std::ref(a), 15.15 ),
        button()
    } ;

    for( button& b : my_buttons ) b.click() ;
    std::cout << "--------------------\n" ;

    const auto clicked = []( button& b )
    { std::cout << "main::closure0: button with id " << b.id << " was clicked\n" ; } ;

    for( button& b : my_buttons ) b.subscribe( clicked, b ) ;
    my_buttons[1].subscribe( [] { std::cout << "main::closure1: one more subscription for this button\n" ; } ) ;
    for( button& b : my_buttons ) b.click() ;
}
