#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <random>

namespace concurrency {
using namespace std;
using namespace std::chrono;

class MyFunctor
{
private:
    const string name;
    const int sleepTime;

public:
    explicit MyFunctor(const string name, const int sleepTime): 
        name(name), sleepTime(sleepTime) {}

    void operator()() {
        this_thread::sleep_for(milliseconds(sleepTime));
        cout << name << " slept for " << sleepTime << " msec" << endl;
    }
};
}

int main()
{
    using namespace std;
    using namespace concurrency;

    random_device randomDevice;
    mt19937 engine(randomDevice());
    uniform_int_distribution<> random(0, 1000);

    MyFunctor functorOne("Thread 1", random(engine));
    MyFunctor functorTwo("Thread 2", random(engine));

    thread threadOne(functorOne);
    thread threadTwo(functorTwo);
    threadOne.join();
    threadTwo.join();
    return 0;
}