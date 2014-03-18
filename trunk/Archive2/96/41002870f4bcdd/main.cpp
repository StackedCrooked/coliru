#include <iostream>
#include <thread>
#include <unistd.h>

class TestModule
{
public:
    virtual ~TestModule() = default;

    void run()
    {
        // create the thread
        thrd = std::thread(&TestModule::_run, this);
    }

protected:
    std::thread thrd;                       // the running thread

private:
    void _run()
    {
        int counter = 0;
        while (true) {
            sleep(5);   // pretend to do stuff
            std::cerr << "I'm a thread: " << counter++ << std::endl;
        }
    }
};

int main() {
    TestModule app;
    app.run();

    int counter = 0;
    while (true) {
        sleep(2);
        std::cerr << "I am main: " << counter++ << std::endl;
    }
}
