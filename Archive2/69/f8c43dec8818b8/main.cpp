#include <cassert>
#include <chrono>
#include <iostream>
#include <thread>

class Timer {
    typedef std::chrono::high_resolution_clock Time;
    typedef std::chrono::duration<float> duration;

    Time::time_point m_timestamp;
    duration currentElapsed;

public:
    Timer() : m_timestamp(Time::now()) {}

    duration getCurrentElapsed() const {
        return currentElapsed;
    }
    
    void Tick() {
        auto now = Time::now();
        currentElapsed = now - m_timestamp;
        m_timestamp = now;
    }
};

int main() {
    Timer t;
    std::this_thread::sleep_for(std::chrono::milliseconds{250});
    t.Tick();
    std::cout << t.getCurrentElapsed().count() << '\n';
}
