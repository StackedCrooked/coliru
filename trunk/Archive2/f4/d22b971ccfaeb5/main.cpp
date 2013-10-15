//#include <boost\thread\thread_only.hpp>
#include <iostream>
//#pragma comment(lib, "libboost_thread-vc100-mt-gd-1_54.lib")
//#define BOOST_LIB_NAME libboost_thread-vc100-mt-gd-1_54.lib
#include <thread>

using namespace std;

struct callable
{
    void operator()()
    {
        std::cout << "Threading test !\n";
    }
};


thread createThread()
{
    callable x;
    return thread(x);
}
int main()
{
    thread th = createThread();
    th.join();


}