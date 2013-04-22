#include <thread>
#include <vector>
#include <atomic>
#include <iostream>

class Thread {
private:
    std::thread thrd;
    std::atomic<bool> done;
    
public:

    template <typename Fx, typename ...T>
    Thread ( Fx&& fx, T&&... args ) : thrd( fx, std::forward( args )... ), done( true ) {
        
    }
    
    bool Done () const {
        return done;
    }
    
    void Join () {
        thrd.join();
    }
};

void abc ( int val ) {
    std::cout << val << std::endl;
}

int main () {
    Thread t(&abc, 1);
    t.Join();
}
