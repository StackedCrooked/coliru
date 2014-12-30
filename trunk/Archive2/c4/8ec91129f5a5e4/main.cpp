#include <stdexcept>
#include <mutex>
#include <iostream>

void call_locked(const std::unique_lock<std::mutex>& A) {
    if(!A.owns_lock()) // possible with e.g. std::defer_lock
        throw std::logic_error("Not locked you jarhead!");
        
    std::cout << "call_locked: A is locked\n";
}

int main() {
    std::mutex mymutex;
    std::unique_lock<std::mutex> mylock(mymutex);
    
    if(mylock.owns_lock())
        std::cout << "main: mylock is locked\n";
        
    call_locked(mylock);
    
    if(mylock.owns_lock())
        std::cout << "main: mylock is still locked\n";
}
