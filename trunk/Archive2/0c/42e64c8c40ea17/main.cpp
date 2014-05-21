#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <queue>
#include <atomic>
#include <string>
#include <fstream>

struct thread_pool
{
    explicit thread_pool( std::size_t nthreads = 4 )
    { while( threads.size() <  nthreads ) threads.emplace_back( thread(*this) ) ; }

    ~thread_pool()
    {
        stopping = true ;
        cv.notify_all() ;
        for( auto& t : threads ) t.join() ;
    }

    template < typename FN, typename... ARGS >
    void push( FN fn, ARGS&&... args )
    {
        {
            std::unique_lock<std::mutex> lock(mutex) ;
            tasks.emplace( std::bind( fn, std::forward<ARGS>(args)... ) ) ;
        }
        cv.notify_one() ;
    }

private:
    thread_pool( const thread_pool& ) = delete ;
    thread_pool& operator= ( const thread_pool& ) = delete ;

    std::vector< std::thread > threads ;
    std::queue< std::function< void() > > tasks ;

    std::mutex mutex ;
    std::condition_variable cv ;
    std::atomic<bool> stopping { false } ;

    struct thread
    {
        thread( thread_pool& p ) : pool(p) {}

        thread_pool& pool ;

        void operator() () const
        {
            while( !pool.stopping )
            {
                std::function< void() > task ;

                {
                    std::unique_lock<std::mutex> lock( pool.mutex ) ;
                    while( !pool.stopping && pool.tasks.empty() ) pool.cv.wait(lock) ;
                    if( pool.stopping ) return ;

                    task = pool.tasks.front() ;
                    pool.tasks.pop() ;
                }

                task() ;
            }
        }
    };
};

struct find_in_file
{
    void operator() ( const char* file_name, const std::string& goal_string )
    {
        std::ifstream file( file_name ) ;
        std::string line ;
        while( std::getline(file,line) )
        {
            if( line.find(goal_string) != std::string::npos )
            {
                std::lock_guard<std::mutex> lock(mutex) ;
                result.emplace_back(file_name) ;
                return ;
            }
        }
    }

    static std::vector<std::string> result ;
    static std::mutex mutex ;
};

std::vector<std::string> find_in_file::result ;
std::mutex find_in_file::mutex ;

int main()
{
    const std::string goal_string = "arbitrary precision" ;
    
    {
       thread_pool pool ;

       pool.push( [] { std::cout << "hello world!\n" << std::flush ; } ) ;
       
       const char* files[] = { __FILE__, "/usr/share/doc/bc/README", "/usr/share/doc/bison/README" } ;
       for( auto f : files ) pool.push( find_in_file(), f, goal_string ) ;

       pool.push( [] { std::cout << "hello again!\n" << std::flush ; } ) ;
       
       std::this_thread::sleep_for( std::chrono::seconds(1) ) ;
    }

    for( auto& str : find_in_file::result ) 
        std::cout << '\'' << goal_string << "' was found in file " << str << '\n' ;
}
