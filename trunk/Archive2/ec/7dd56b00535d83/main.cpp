#include <iostream>
#include <thread>
#include <future>
#include <mutex>

struct A
{
    double run( int a, long b, float c ) const
    {
        static std::mutex stdout_guard ;
        {
            std::lock_guard<std::mutex> lock(stdout_guard) ;
            std::cout << "thread: " << std::this_thread::get_id() 
                      << "  function: A::run  args: " << this << " (this)  "
                      << a << " (a)  " << b << " (b)  "  << c << " (c)\n" << std::flush ;
        }
        
        return a+b+c+v ;          
    }
    
    int v = 10 ;
};

int main()
{
    A a ;
    A* pa = std::addressof(a) ;
    std::cout << "thread: " << std::this_thread::get_id()<< " (main)  address of a: " << pa << '\n' << std::flush ; 
    
    auto future = std::async( std::launch::async, &A::run /* function */, pa /* pointer to object */, 1, 2, 3.4 ) ;
    
    std::thread thread( &A::run /* function */, pa /* pointer to object */, 1, 2, 3.4 ) ;

    thread.join() ;
    
    future.wait() ;
    std::cout << "async result: " << future.get() << '\n' ;
}
