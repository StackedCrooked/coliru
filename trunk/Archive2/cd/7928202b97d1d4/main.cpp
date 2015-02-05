#include <boost/thread/mutex.hpp>

boost::mutex mutex_lock;

int main(int argc, char **argv)
{
    bool ret = mutex_lock.try_lock();
    if(ret != true)
        std::cout << "failed" << std::endl;
    else
    {
        std::cout << "yeah" << std::endl;
        mutex_lock.unlock();
    }
}