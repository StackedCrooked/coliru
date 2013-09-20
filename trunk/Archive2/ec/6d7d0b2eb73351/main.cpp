#include <iostream>
#include <thread>
 
int main() {
    std::thread([](){
        std::cout << "moin" << std::endl;
    }).join();
}