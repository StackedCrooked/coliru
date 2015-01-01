#include <thread>
#include <condition_variable>
#include <iostream>
#include <queue>
#include <chrono>
#include <iomanip>

std::mutex m_queueMutex;
std::condition_variable m_pushCondition;

std::queue<int> m_queue;

template <typename Rep, typename Period>
bool pop(std::chrono::duration<Rep, Period> waitTime, int& item)
{
    std::cv_status cvStatus = std::cv_status::no_timeout;
    std::unique_lock<std::mutex> lock(m_queueMutex);

    while (m_queue.empty() && (cvStatus == std::cv_status::no_timeout))
    {
        cvStatus = m_pushCondition.wait_for(lock, waitTime);
    }

    if (cvStatus == std::cv_status::no_timeout)
    {
        item = std::move(m_queue.front());
        m_queue.pop();
        return true;
    }

    return false;
}

int main() {
    int data;
    pop(std::chrono::seconds(2), data);
}
