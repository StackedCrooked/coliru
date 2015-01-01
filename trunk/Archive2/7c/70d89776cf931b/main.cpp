#include <thread>
#include <condition_variable>
#include <iostream>
#include <deque>
#include <chrono>
#include <iomanip>

std::mutex m_queueMutex;
std::condition_variable m_pushCondition;

std::deque<int> m_queue;

template <typename Rep, typename Period>
bool pop(std::chrono::duration<Rep, Period> waitTime, int& popped)
{
    std::unique_lock<std::mutex> lock(m_queueMutex);

    if (m_pushCondition.wait_for(lock, waitTime, [] { return !m_queue.empty(); }))
    {
        popped = m_queue.back();
        m_queue.pop_back();
        return true;
    } else
    {
        return false;
    }
}

int main()
{
    int data;
    using namespace std::chrono;

    pop(seconds(2)    , data);

    std::cout << std::hex << std::showbase << seconds::max().count() << "\n";
    auto time = steady_clock::now() + seconds::max();
    std::cout << std::dec << duration_cast<seconds>(time.time_since_epoch()).count() << "\n";
    pop(seconds::max(), data);
}
