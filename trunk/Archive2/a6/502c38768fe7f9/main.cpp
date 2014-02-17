#include <iostream>
#include <atomic>
#include <future>
#include <vector>
#include <chrono>
#include <functional>

struct some_task
{
    int operator() ( int a ) const 
    {
        std::cout << "start task\n" << std::flush ;
        ++cnt ;
        
        // ...
        std::this_thread::sleep_for( std::chrono::milliseconds(500) ) ;
        
        return a*a ;
    }
    
    static std::atomic<int> cnt ;
};

std::atomic<int> some_task::cnt {0} ;

int main()
{
    int ss = 0 ;
    std::vector< std::future<int> > results ;
    
    // simple asynchronous execution of tasks
    for( int i = 0 ; i < 5 ; ++i )
    {
        // launch a task asynchronously
        results.emplace_back( std::async( std::launch::async, some_task(), i ) ) ;
    }
    std::cout << "**** launched five asynchronous tasks\n" << std::flush ;

    // asynchronous execution of tasks in designated threads
    std::vector< std::thread > threads ;
    for( int i = 5 ; i < 10 ; ++i )
    {
        std::packaged_task< int() >  task( std::bind( some_task(), i ) ) ; // create a task
        results.emplace_back( task.get_future() ) ;
        threads.emplace_back( std::thread( std::move(task) ) ) ; // give it to a thread
    }
    std::cout << "**** launched five packaged tasks\n" << std::flush ;
    
    std::cout << "**** waiting for results...\n" << std::flush ;
    for( auto& t : threads ) t.join() ; // wai for threads to complete
    for( auto& f : results ) ss += f.get() ; // get the results
    
    // print out the number of times the task was executed
    std::cout << "**** done.\n**** function was called " << some_task::cnt << " times.\n"
              << "sum of results: "  << ss << '\n' ;
}
