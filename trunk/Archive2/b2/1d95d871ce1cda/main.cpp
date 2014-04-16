#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread.hpp>

namespace pt = boost::posix_time;

struct Dummy
{
    std::unique_ptr<pt::ptime> m_time;
    int m_iMediatime = 1; // seconds

    Dummy() : m_time(new pt::ptime(pt::microsec_clock::local_time()))
    {
    }

    void foo() const
    {
        const pt::ptime now = pt::microsec_clock::local_time();

        if (m_time != NULL)
        { 
            auto delta = now - *m_time;
            if (delta > pt::milliseconds(this->m_iMediatime * 1000))
            {
                std::cout << "yay\n";
            }
            else
            {
                std::cout << "nay\n";
            }
        }
    }
};

int main()
{
    Dummy o;
    o.foo();

    boost::this_thread::sleep_for(boost::chrono::seconds(2));

    o.foo();
}
