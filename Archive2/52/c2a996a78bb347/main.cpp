#include <iostream>
#include <boost/asio.hpp>
#include <boost/optional.hpp>
#include <boost/thread.hpp>

class A
{
    using ios = boost::asio::io_service;

    ios                        m_io;
    boost::optional<ios::work> m_active;
  public:
    A() : m_io(), m_active(ios::work(m_io)) {}

    ~A() {
        m_active.reset();
        m_io.run(); // to completion
    }

    void update()
    {
        m_io.poll();
        //do other stuff
    }

    void postSomething()
    {
        int i = 0;
        while(m_active)
        {
            m_io.post([&]{std::cout<<"something" << ++i << "\n";});
            boost::this_thread::sleep_for(boost::chrono::milliseconds(250));
        }
    }
};

int main()
{
    boost::thread thr;
    {
        A a;

        thr = boost::thread(boost::bind(&A::postSomething, &a));

        for (int i = 0; i < 300; ++i)
        {
            boost::this_thread::sleep_for(boost::chrono::milliseconds(5));
            a.update();
        }
    }

    thr.join(); // thread will not join unless A is destructed (m_active is cleared)
}
