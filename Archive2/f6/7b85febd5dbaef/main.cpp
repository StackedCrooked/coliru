//#include <mutex>
#include <thread>
#include <condition_variable>
typedef int ComplexType;
std::mutex m;
std::condition_variable cv;
 
bool ready = false;
ComplexType result;  // some arbitrary type
 
void thread_func()
{
    std::unique_lock<std::mutex> lk(m);
    // assign a value to result using thread_local data
    result = function_that_uses_thread_locals();
    ready = true;
    std::notify_all_at_thread_exit(cv, std::move(lk));
} // 1. destroy thread_locals, 2. unlock mutex, 3. notify cv
 
int main()
{
    std::thread t(thread_func);
    t.detach();
 
    // do other work
    // ...
 
    // wait for the detached thread
    std::unique_lock<std::mutex> lk(m);
    while(!ready) {
        cv.wait(lk);
    }
    process(result); // result is ready and thread_local destructors have finished
}