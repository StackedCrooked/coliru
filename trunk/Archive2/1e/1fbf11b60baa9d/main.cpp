#include <iostream>
#include <csignal>
#include <thread>
#include <chrono>
#include <functional>

static volatile std::sig_atomic_t flag ;

void set_flag( int signal ) { flag = signal ; }

struct A 
{ 
    int n = 0 ; 
    void mem_fun() { std::cout << ++n << ". A::mem_fun\n" ; /* do whatever */ } 
};

void process_signal( A& object )
{
    while( flag != SIGTERM )
    {
        if( flag == SIGINT )
        {
            flag = 0 ;
            object.mem_fun() ;
        }
        std::this_thread::sleep_for( std::chrono::milliseconds(100) ) ;
    }
    std::cout << "quitting on SIGTERM\n" ;
}

int main()
{
    A a ;
    std::thread worker( process_signal, std::ref(a) ) ;
    std::signal( SIGINT, set_flag ) ;
    std::signal( SIGTERM, set_flag ) ;

    for( int i = 0 ; i < 5 ; ++i )
    {
        std::raise(SIGINT) ;
        std::this_thread::sleep_for( std::chrono::milliseconds(200) ) ;
    }

    std::raise(SIGTERM) ;
    worker.join() ;
}
