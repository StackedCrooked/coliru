#include <boost/thread.hpp>

boost::atomic_bool data1_received(false);
boost::atomic_bool data2_received(false);

bool check_data_received()
{
    return (data1_received && data2_received);
}

void thread1()
{
    while (!check_data_received())
    {
        boost::this_thread::sleep_for(boost::chrono::microseconds(1));
    }
    std::cout << "Everybody here";
}

void thread2()
{
    boost::this_thread::sleep_for(boost::chrono::milliseconds(rand() % 14000));
    data1_received = true;
}

void thread3()
{
    boost::this_thread::sleep_for(boost::chrono::milliseconds(rand() % 14000));
    data2_received = true;
}

int main()
{
    boost::thread_group g;
    g.create_thread(thread1);
    g.create_thread(thread2);
    g.create_thread(thread3);

    g.join_all();
}
