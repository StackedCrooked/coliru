#include <iostream>
#include <boost/enable_shared_from_this.hpp>
#include <boost/make_shared.hpp>
#include <boost/thread.hpp>
#include <boost/signals2.hpp>
#include <boost/bind.hpp>
using namespace std;
using namespace boost;

struct Object : boost::enable_shared_from_this<Object>
{
    Object() : x(0)        {cout << __PRETTY_FUNCTION__ << endl;}
    virtual ~Object()      {cout << __PRETTY_FUNCTION__ << endl;} 

    void doSomething()
    {
        this_thread::sleep(posix_time::milliseconds(4200));
        cout << "Accessing member in " << __PRETTY_FUNCTION__ << endl;
        x++;
    }

    int x;
};

class Worker
{
public:
    Worker() {}
    virtual ~Worker() {myThread.join();}
    void Start() { myThread = thread(bind(&Worker::DoThread, this)); }

    signals2::signal<void ()>  Signal;

private:
    void DoThread()
    {   // thread B
        Signal();
    }

    thread myThread;
};

int main()
{
    Worker w;

    {   // thread A
        auto o = boost::make_shared<Object>();
        signals2::connection bc = w.Signal.connect(bind(&Object::doSomething, o));
        w.Start();
        this_thread::sleep(posix_time::seconds(2));
        bc.disconnect();
    }

    return 0;
}
