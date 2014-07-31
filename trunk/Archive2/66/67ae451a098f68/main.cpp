#include <mutex>

int main()
{
    using std::mutex;
    using std::lock_guard;
    
    lock_guard<mutex> lg(mutex);
}
