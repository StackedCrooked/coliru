#include <mutex>
#include <thread>
#include <condition_variable>

std::mutex m;
std::condition_variable cv;

bool ready = false;

void thread_func()
{
    std::unique_lock<std::mutex> lk(m);
    ready = true;
    std::notify_all_at_thread_exit(cv, std::move(lk));
}

int main()
{
    std::thread t(thread_func);
    t.detach();

    std::unique_lock<std::mutex> lk(m);
    while(!ready) {
        cv.wait(lk);
    }
}
