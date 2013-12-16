#include <iostream>
#include <functional>
#include <queue>
#include <string>

struct task_queue
{
    template < typename CALLABLE, typename... ARGS >
    void run_when_asked( CALLABLE fn, ARGS&&... args )
    { pending.push( std::bind( fn, args... ) ) ; }

    void execute_pending()
    {
        while( !pending.empty() )
        {
            pending.front()() ;
            pending.pop() ;
        }
    }

    std::queue< std::function< void() > > pending ;
};

int free_fun( int a, int b )
{
    std::cout << "free_fun(" << a << ',' << b << ")\n" ;
    return a+b ;
}

struct function_object
{
    void operator() ( const std::string& str ) const
    { std::cout << "function_object()(" << str << ")\n" ; }
};

struct some_class
{
    double mem_fun( double a, double b ) const
    {
        std::cout << "some_class::mem_fun( (" << this << "), " << a << ", " << b << " )\n" ;
        return a+b+v ;
    }
    int v = 7 ;
};


int main()
{
    task_queue tq ;
    tq.run_when_asked( free_fun, 1, 2 ) ;

    function_object f ;
    tq.run_when_asked( f, "hello world" ) ;

    some_class obj ;
    tq.run_when_asked( &some_class::mem_fun, std::ref(obj), 3.4, 5.6 ) ;

    tq.run_when_asked( [] ( int a, int b )
                       { std::cout << "closure(" << a << ',' << b << ")\n" ; },
                       5, 6 ) ;

    tq.execute_pending() ;
}
