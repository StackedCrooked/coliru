#include <thread>
#include <vector>

//////////////////////////////////////////////////////////
// fake external library taking a callback
extern void library_function(int, void(*cb)(int,int));

//////////////////////////////////////////////////////////
// our client code
#include <iostream>
#include <mutex>

void callback_handler(int i, int input)
{
    static std::mutex mx;
    std::lock_guard<std::mutex> lk(mx);
    std::cout << "Callback #" << i << " from task for input " << input << "\n";
}

//////////////////////////////////////////////////////////
// callback queue
#include <deque>
#include <future>

namespace {
    using pending_callback = std::packaged_task<void()>;
    std::deque<pending_callback> callbacks;
    std::mutex callback_mutex;

    int process_pending_callbacks() {
        std::lock_guard<std::mutex> lk(callback_mutex);

        int processed = 0;
        while (!callbacks.empty()) {
            callbacks.front()();
            ++processed;
            callbacks.pop_front();
        }

        return processed;
    }

    void enqueue(pending_callback cb) {
        std::lock_guard<std::mutex> lk(callback_mutex);
        callbacks.push_back(std::move(cb));
    }
}

// this wrapper to "fake" a callback (instead queuing the real
// callback_handler)
void queue_callback(int i, int input)
{
    enqueue(pending_callback(std::bind(callback_handler, i, input)));
}

int main()
{
    // do something with delayed processing:
    library_function(3, queue_callback);
    library_function(5, queue_callback);

    // wait for completion, periodically checking for pending callbacks
    for (
        int still_pending = 3 + 5; 
        still_pending > 0; 
        std::this_thread::sleep_for(std::chrono::milliseconds(10))) // no busy wait
    {
        still_pending -= process_pending_callbacks();
    }
}

// somewhere, in another library:

#include <chrono>
void library_function(int some_input, void(*cb)(int,int))
{
    std::thread([=] {
        for (int i = 1; i <= some_input; ++i) {
            std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 5000)); // TODO abolish rand()
            cb(i, some_input);
        }
    }).detach();
}

