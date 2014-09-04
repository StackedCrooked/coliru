#include <iostream>
#include <chrono>


template</*std::chrono::duration D*/>
    D difference(std::chrono::time_pont start, std::chrono::time_point stop)
    {
        return std::chrono::duration_cast<D>(stop-start);
    }


        
int main(void) 
{ 
    
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    // sleep
    std::this_thread::sleep_for(std::chrono::seconds(1));
    //
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    // get difference
    auto res = difference<std::chrono::seconds>(start, stop);
    
    // print
    std::cout << res.count()
              << std::endl;

}



