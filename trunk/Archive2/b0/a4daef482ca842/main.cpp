#include <iostream>
#include <string>
#include <vector>

#include <boost/chrono.hpp>
#include <boost/thread/condition_variable.hpp>
#include <boost/thread/mutex.hpp>

using namespace boost;

int main() {
    mutex mtx;
    condition_variable cond;
    
    unique_lock<mutex> lk(mtx);
    
    std::cout << BOOST_VERSION << "\n";
    
    for(int i=0; i<10; i++) {
        std::cout << i << " : " << chrono::steady_clock::now() << "\n";
        if (cv_status::no_timeout == cond.wait_for(lk, chrono::seconds(1)))
            std::cout << "no_timeout\n";
    }
}
