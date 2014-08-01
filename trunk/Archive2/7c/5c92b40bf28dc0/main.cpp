#include <iostream>
#include <boost/thread.hpp>
#include <boost/chrono.hpp>


int main()
{
    boost::shared_mutex mutex;
    
    boost::shared_lock<boost::shared_mutex> l1(mutex);
    boost::shared_lock<boost::shared_mutex> l2(mutex);
    
    std::cout << "Not blocked" << std::endl
              << std::boolalpha << "Owns l1: " << l1.owns_lock() << std::endl
                                << "Owns l2: " << l2.owns_lock() << std::endl;
    
}
