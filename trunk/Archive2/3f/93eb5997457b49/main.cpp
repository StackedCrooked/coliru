#include <boost/thread.hpp>
#include <iostream>

struct parallel {
    boost::thread m_Thread;
    void stop() { std::cout << "whatever this does\n"; }
    void start() {
        m_Thread = boost::thread(&parallel::stop,this);
    }
};
int main()
{
    parallel x;
    x.start();
    x.m_Thread.join();
    std::cout << "done\n";
}
    