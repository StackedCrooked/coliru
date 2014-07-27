#include <iostream>
#include <iomanip>
#include <boost/thread/thread.hpp>

int main()
{
    boost::thread *p = new boost::thread("thread1");
    return 0;
}
