#include <boost/thread.hpp>
#include <iostream>
int main()
{
    boost::thread([]{ std::cout << "thread" << std::endl; }).join();
}