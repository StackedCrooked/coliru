#include <cassert>
#include <chrono>
#include <iostream>
#include <thread>

void sleep(unsigned n) {
    std::this_thread::sleep_for(std::chrono::milliseconds{50*n});
}

class TestModule
{
public:
    ~TestModule() {
        if (thrd.joinable()) thrd.join();
    }

    void run() {
        assert(!thrd.joinable());
        thrd = std::thread(&TestModule::_run, this);
    }

private:
    std::thread thrd;                       // the running thread
    void _run() {
        std::cout << "I'm a thread: hello!" << std::endl;
        for (int count = 0; count < 4; ++count) {
            sleep(2);   // pretend to do stuff
            std::cout << "I'm a thread: " << count << std::endl;
        }
        std::cout << "I'm a thread: bye!" << std::endl;
    }
};

int main() {
    TestModule app;
    app.run();

    for (int count = 0; count < 8; ++count) {
        sleep(1);
        std::cout << "I'm main: " << count <<std::endl;
    }
    std::cout << "All done.\n";
}
