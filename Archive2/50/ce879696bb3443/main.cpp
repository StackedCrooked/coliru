#include <cassert>
#include <cstdint>
#include <functional>
#include <mutex>
#include <iostream>
#include <string>
#include <thread>
#include "tbb/concurrent_queue.h"


struct Internal {};
struct External {};


std::mutex print_mutex;


#define TRACE []{ \
    std::lock_guard<std::mutex> lock(print_mutex); \
    std::cout << __FILE__ << ':' << __LINE__ << ": " << __PRETTY_FUNCTION__ << std::endl; \
}();



struct Stack
{
    Stack() :
        mDispatchThread([this]{ dispatch_thread(); }),
        mChecksumThread([this]{ checksum_thread(); })
    {
        TRACE
    }

    ~Stack()
    {
        TRACE
        mChecksumQueue.push(std::string());

        TRACE
        mDispatchQueue.push(std::function<void(Internal)>());

        TRACE
        mChecksumThread.join();

        TRACE
        mDispatchThread.join();
    }


    std::string get_send_data()
    {
        TRACE
        return "012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789";
    }


    void send_all()
    {
        TRACE
        std::string s = get_send_data();
        mChecksumQueue.push(s);
    }

    void push(Internal, std::string s)
    {
        std::lock_guard<std::mutex> lock(print_mutex);
        std::cout << "Pushing " << s << std::endl;
    }


private:
    void dispatch_thread()
    {
        for (;;)
        {
            std::function<void(Internal)> f;
            mDispatchQueue.pop(f);
            if (!f)
            {
                return;
            }

            f(Internal{});
        }
    }
    void checksum_thread()
    {
        for (;;)
        {
            std::string s;
            mChecksumQueue.pop(s);

            if (s.empty())
            {
                return;
            }

            assert(s.size() >= sizeof(uint32_t));

            uint32_t sum = 0;

            for (auto c : s)
            {
                sum += uint8_t(c);
            }

            while (sum > 0xFFFF)
            {
                sum = (sum >> 16) + (sum & 0xFFFF);
            }

            memcpy(&s[0], &sum, sizeof(sum));

            mDispatchQueue.push([=](Internal in) {
                push(in, s);
            });
        }
    }

    tbb::concurrent_bounded_queue<std::function<void(Internal)>> mDispatchQueue;
    tbb::concurrent_bounded_queue<std::string> mChecksumQueue;

    std::thread mDispatchThread;
    std::thread mChecksumThread;
};


int main()
{
    std::thread([]{
        std::this_thread::sleep_for(std::chrono::seconds(5));
        { std::lock_guard<std::mutex> lock(print_mutex); std::cout << "TIMEOUT" << std::endl; }
        std::abort();
    }).detach();

    Stack stack;

    stack.send_all();

    //std::this_thread::sleep_for(std::chrono::seconds(1));
}
