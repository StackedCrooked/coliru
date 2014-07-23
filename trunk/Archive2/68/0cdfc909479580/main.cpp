#include <iostream>
#include <future>
#include <thread>
#include <chrono>
using namespace std;

int main() {
    std::future<int> future = std::async(std::launch::async, [](){ 
        std::this_thread::sleep_for(std::chrono::seconds(3));
        return 8;  
    });
    
    std::future_status status = future.wait_for(std::chrono::seconds(5));
    if (status == std::future_status::timeout) {
        std::cout << "Timeout" <<endl ;
    } else{
    	cout << "Success" <<endl ;
    } // will print Success
    
    std::future<int> future2 = std::async(std::launch::async, [](){ 
        std::this_thread::sleep_for(std::chrono::seconds(3));
        return 8;  
    });
    
    std::future_status status2 = future2.wait_for(std::chrono::seconds(1));
    if (status2 == std::future_status::timeout) {
        std::cout << "Timeout" <<endl ;
    } else{
    	cout << "Success" <<endl ;
    } // will print Timeout
    
    std::this_thread::sleep_for(std::chrono::seconds(8));
	return 0;
}