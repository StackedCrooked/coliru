/* Mutlithreading Example
   Author         : _P0W!
   Compiled using :
                    clang++  main.cpp -std=c++11 -Wall -Wextra -O2  && ./a.out
   
   Not used Boost : (-lboost_thread -lboost_system ) 
   
   Referred : https://www.youtube.com/watch?v=3ZxZPeXPaM4 (C++ Threading #3: Data Race and Mutex)
*/
/*
    Data Race
    1. Using Mutex -> simple method
        std::mutex mu; // global
        void foo()
        {
            mu.lock();
            //...
            mu.unlock();
        }
        Problems :
        a) when execption occurs in //... section mu remains locked
        b) mu is global anyone can re use it
        
    2. Using std::lock_guard it basically provide RAII mechanish for a mutex
       
        std::mutex mu; // global
        void foo()
        {
            std::lock_guard< std::mutex > guard(mu) ;
            // ...
        }
        Problems :
        a) mu is still global
        
    3. Use a wrapper class to bind the resource with mutex guard.
    class LockResource
    {
        std::ostream& os;
        std::mutex mu ; // no longer global
        
        public:
            LockResource( std::ostream& t) : os(t) { }
            disp( Args arg )
            {
                std::lock_guard< std::mutex > guard(mu) ;
                // ...
            }
    };
    
    Things to remember
    a) Never return os
    b) Never pass os to other member functions
       
    
*/

#include <iostream>
#include <thread>
#include <mutex>

template<typename T>
class LockResource 
{
    T& res ;
    std::mutex mu ;
    
    public:
    LockResource(  T& t): res(t)
    { }
    
    void disp( const std::string& str, const int& i )
    {
     std::lock_guard<std::mutex> guard(mu);
     res << str << i << "[ Thread ID: " << std::this_thread::get_id() << " ]" <<  '\n';
    }
    
};

int foo( LockResource<std::ostream>& lr )
{
    for(int i=10 ; i>=1 ; --i )
    {
      // lr.disp("Foo cries :" , 100 -i ) ;
       lr.disp( "foo says ", i);
    }
    return 0;
}

int bar(LockResource<std::ostream>& lr )
{
    for(int i=1 ; i<=10 ; ++i )
    {
        // lr.disp("Bar cries :" , 100 -i ) ;
         lr.disp( "bar says ", i);
    }
    return 0;
}


int main()
{
 
   LockResource<std::ostream> con(std::cout) ;
   std::thread t1( foo, std::ref(con) )     ;
   std::thread t2( bar, std::ref(con) ) ;
   t1.join( );
   t2.join( );
}