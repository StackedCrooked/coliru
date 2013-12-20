#include <cassert>
#include <chrono>
#include <iostream>
#include <thread>

int main() {
    using namespace std::chrono;
    assert(duration_cast<seconds>(milliseconds{999}) == seconds{0});

    typedef high_resolution_clock Time;
    typedef duration<float> fsec;

    auto m_timestamp = Time::now();
    std::this_thread::sleep_for(milliseconds{250});
    std::cout << duration_cast<duration<float,std::milli>>(Time::now() - m_timestamp).count() << '\n';
}
