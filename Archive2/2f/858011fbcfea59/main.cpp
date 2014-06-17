#include <boost/signals2/signal.hpp>
#include <boost/timer.hpp>
#include <boost/progress.hpp>
#include <fstream>
#include <iostream>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>

struct Data {
    int iterations = 1000;
};

class Foo
{
  public:
    template <typename L>
    void attachListener(L const &listener)
    {
        m_callback.connect(listener);
    }

    void doWork()
    {
        for (int i = 0; i < m_someData; ++i) {
            m_callback(m_someData);
            boost::this_thread::sleep_for(boost::chrono::milliseconds(2));
        }
    }
    Data m_someData;
  private:
    boost::signals2::signal<void(Data const&)> m_callback;

};

void callback(Data const &/*someData*/, boost::progress_display &pd)
{
   ++pd; // other stuff
}

void otherFunction()
{
    Foo foo;
    boost::progress_display pd(foo.m_someData.iterations); 

    boost::function<void(Data const&)> f(boost::bind(&callback, _1, boost::ref(pd)));

    foo.attachListener(f);
    foo.doWork();
}

int main()
{
    otherFunction();
}
