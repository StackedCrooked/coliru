#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>
#include <string>
#include <atomic>

struct signal_recvr
{

    void recv_signal( std::string signal )
    {
        ++i ;
        if( signal == "now" ) wait_and_calculate() ;
        else std::thread( &signal_recvr::calculate, this ).detach() ;
    }

    ~signal_recvr()
    {
        while( thread_cnt > 0 ) std::this_thread::sleep_for( std::chrono::milliseconds(10) ) ;
        std::lock_guard<std::mutex> guard(result_lock) ;
        for( int v : result ) std::cout << v << ' ' ; std::cout << '\n' ;
    }
    
    private:
        void calculate()
        {
            ++thread_cnt ;
            std::lock_guard<std::mutex> guard(result_lock) ;
            result.push_back(  100 - i ) ;
            --thread_cnt ;
        }
    
        void wait_and_calculate()
        {
            std::this_thread::sleep_for( std::chrono::seconds(1) ) ;
            std::lock_guard<std::mutex> guard(result_lock) ;
            result.push_back(i) ;
        }
    
        std::atomic<int> i {0} ;
        
        std::atomic<int> thread_cnt {0} ;
        
        std::vector<int> result ;
        std::mutex result_lock ;
};

int main()
{
    signal_recvr recvr ;
    for( int i = 0 ; i < 10 ; ++i )
    {
        recvr.recv_signal( i%2 ? "now" : "later" ) ;
        std::this_thread::sleep_for( std::chrono::milliseconds(1) ) ;
    }
}
