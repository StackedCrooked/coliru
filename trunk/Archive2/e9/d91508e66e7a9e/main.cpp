#include "tbb/concurrent_queue.h"
#include <atomic>
#include <future>
#include <mutex>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <unistd.h>

// thread-safe logging
auto print = [](const char* msg){
    static std::mutex fMutex;
    std::lock_guard<std::mutex> lock(fMutex);
    std::cout << msg << std::endl;
};

// trace macro which prints the current function with full signature
#define TRACE print(__PRETTY_FUNCTION__);


struct Stack;
struct Protocol;
struct Session;

// the "KEY" to prevent unsafe access to the stack
// all internal methods receive an Internal object as first argument
class Internal {
    Internal() {}  // constructor is private
    friend struct Stack; // Only the Stack can create it.
};

struct Session
{
    Session(Internal, Protocol& protocol);

    // disable copy and copy assignment
    Session(const Session&) = delete;
    Session& operator=(const Session&) = delete;

    // enable move and move assignment
    Session(Session&&) = default;
    Session& operator=(Session&&) = default;

    bool start(Internal) {
        TRACE
        return true;
    }

    bool stop(Internal) {
        TRACE
        return true;
    }

    // external implementations (implemented later)
    std::future<bool> start();
    std::future<bool> stop();

private:
    Protocol* protocol_;
    Stack* stack_;
};

struct Protocol
{
    Protocol(Internal, Stack& stack);

    // disable copy and copy assignment
    Protocol(const Protocol&) = delete;
    Protocol& operator=(const Protocol&) = delete;

    // enable move and move assignment
    Protocol(Protocol&&) = default;
    Protocol& operator=(Protocol&&) = default;

    Stack& getStack() { return *stack_; }

    Session& addSession(Internal internal) {
        TRACE
        mSessions.emplace_back(internal, *this);
        return mSessions.back();
    }

    std::future<Session*> addSession();

    bool stop_all(Internal internal) {
        TRACE
        for (auto& session : mSessions)
            session.stop(internal);
        return true;
    }

    std::future<bool> stop_all();

private:
    Stack* stack_;
    std::vector<Session> mSessions;
};

struct Stack
{
    Stack() :
        mQuit(false),
        mInternalThread([=] { this->internal_thread(); })
    {
        TRACE
    }

    // disable copy
    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;

    ~Stack()
    {
        TRACE
        stop_all();
        mInternalThread.join();
    }

    bool stop_all(Internal internal) {
        TRACE
        mQuit = true;
        for (auto& protocol : mProtocols)
            protocol.stop_all(internal);
        return true;
    }

    std::future<bool> stop_all() {
        TRACE
        mQuit = true; // atomic may be set from main thread
        return schedule([=](Internal internal){
            return stop_all(internal);
        });
    }

    Protocol& addProtocol(Internal internal) {
        TRACE
        mProtocols.emplace_back(internal, *this);
        return mProtocols.back();
    }

    std::future<Protocol*> addProtocol() {
        TRACE
        return schedule([=](Internal internal) {
            return &addProtocol(internal);
        });
    }

    // Result is received via callback.
    // Also returns a future. This allows the calling thread
    // to poll the state and wait completion.
    template<typename F>
    auto addProtocol(F&& f) -> std::future<decltype(f(std::declval<Internal>(), std::declval<Protocol&>()))>
    {
        TRACE
        return schedule([=](Internal internal) {
            return f(internal, addProtocol(internal));
        });
    }

    // schedule a function to be executed in the internal thread
    template<typename F>
    auto schedule(F&& f) -> std::future<decltype(f(std::declval<Internal>()))>
    {
        auto promise = std::make_shared<std::promise<decltype(f(std::declval<Internal>()))>>();
        mTasks.push([=] {
            promise->set_value(f(Internal{}));
        });
        return promise->get_future();
    }

private:
    void internal_thread() {
        Task task;
        for (;;) {
            while (mTasks.try_pop(task)) {
                if (mQuit) return;
                task();
            }

            if (mQuit) return;
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }

    std::atomic<bool> mQuit;
    std::vector<Protocol> mProtocols;

    typedef std::function<void()> Task;
    tbb::concurrent_bounded_queue<Task> mTasks;
    std::thread mInternalThread;
};


Protocol::Protocol(Internal, Stack& stack) : stack_(&stack)
{
    TRACE
}


std::future<Session*> Protocol::addSession()
{
    TRACE
    return stack_->schedule([=](Internal internal){
        return &addSession(internal);
    });
}


std::future<bool> Protocol::stop_all()
{
    TRACE
    return stack_->schedule([=](Internal internal){
        return stop_all(internal);
    });
}


Session::Session(Internal, Protocol& protocol) : protocol_(&protocol), stack_(&protocol.getStack())
{
    TRACE
}


std::future<bool> Session::start()
{
    TRACE
    return stack_->schedule([=](Internal internal) {
        return this->start(internal);
    });
}


std::future<bool> Session::stop()
{
    TRACE
    return stack_->schedule([=](Internal internal) {
        return this->stop(internal);
    });
}


// Callbacks may be faster than std::future because they are immediately invoked
// from within the same thread (there is no signal or thread-wakeup involved).
// Callbacks receive the Internal object which allows them to continue calling
// other internal methods without rescheduling.
void test_with_callback()
    try
    {
        print("\n\n*** test_with_callback ***");
        Stack stack;
        std::future<bool> fut = stack.addProtocol([](Internal internal, Protocol& protocol) -> bool {
            Session& session = protocol.addSession(internal);
            session.start(internal);
            session.stop(internal);
            return true;
        });

        if (fut.wait_for(std::chrono::milliseconds(100)) != std::future_status::ready)
        {
            throw std::runtime_error("Timeout occured in callback test.");
        }


    }
    catch (const std::exception& exc)
    {
        print(exc.what());
    }


// using future:
// + nice and natural syntax.
// + very convenient for communicating between threads
// - signals and thread wakeups cost you a few microseconds!
void test_with_futures()
    try
    {
        print("\n\n*** test_with_futures ***");
        Stack stack;
        Protocol& protocol = *stack.addProtocol().get();
        Session& session = *protocol.addSession().get();
        session.start().get();
        session.stop().get();
    }
    catch (const std::exception& exc)
    {
        print(exc.what());
    }


int main()
{
    test_with_futures();
    test_with_callback();
}
