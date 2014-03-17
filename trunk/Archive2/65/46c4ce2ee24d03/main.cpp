#include <thread>
#include <unistd.h>

class TestModule
{
public:
    TestModule(){}
    virtual ~TestModule(){}

    void run()
    {
        // create the thread
        thrd = std::move(std::thread(&TestModule::_run, this));
    }

protected:
    std::thread thrd;                       // the running thread

private:
    void _run()
    {
        while (!true) {
            sleep(5);   // pretend to do stuff
        }
    }
};

class SimpleApp : public TestModule
{
public:
    ~SimpleApp() {}
};

int main() {
    SimpleApp app;
    app.run();

    int ctr=0;
    while (true) {
        sleep(1);
    }
    return 0;
}
