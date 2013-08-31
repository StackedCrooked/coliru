#include <iostream>
#include <thread>

int main() {
    
    std::cout << "Started" << std::endl;
    
    std::thread::id nobody;

    if ( nobody != std::this_thread::get_id() )  {
        
      std::cout << "OK" << std::endl;
    }
    
    std::cout << "Finished" << std::endl;
}

