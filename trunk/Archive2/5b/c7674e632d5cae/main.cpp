#include <thread>

class TestModule
{
public:
    TestModule();
    virtual ~TestModule();

    void run();

protected:
    std::thread thrd;                       // the running thread

private:
    void _run();                            // actual thread loop
    bool bNeedsToQuit;                      // message to terminate
};

//#include "TestModule.h"
#include <iostream>
//#include <unistd.h>
#include <chrono>

TestModule::TestModule() {}

TestModule::~TestModule() {}

void TestModule::run()
{
    // what do we need to do before moving on?
    bNeedsToQuit = false;

    // create the thread
    thrd = std::move(std::thread(&TestModule::_run, this));
}

void TestModule::_run()
{
    while (!bNeedsToQuit) {
        std::this_thread::sleep_for(std::chrono::seconds{5});
        // sleep(5);   // pretend to do stuff
    }
}

#include <string>
#include <boost/format.hpp>

class SimpleApp : public TestModule
{};

int main() {
    SimpleApp app;
    app.run();

    int ctr=0;
    while (1) {
        std::string s = (boost::format(" ctr:%d") %ctr++).str();
//      app.postMessage(s);
        std::this_thread::sleep_for(std::chrono::seconds{1});
        // sleep(1);
    }
}