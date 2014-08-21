#include <iostream>
#include <thread>
#include <mutex>

static std::mutex mtx;
// some mutex defended stuff

void someFunc() {
    // try lock mutex using unique_lock
    std::unique_lock<std::mutex> lock(mtx, std::try_to_lock);
    if(!lock.owns_lock()) {
        return; // locking fails
    }

    // task for thread
    auto task = [&](std::unique_lock<std::mutex>&& lock) {
        // do async work and release lock when it done
        lock.unlock();

        // do something after releasing lock
    };

    // create thread, pass lock 
    std::thread taskThread(task, std::move(lock));
    taskThread.detach();
}

int main()
{
  someFunc();
}
