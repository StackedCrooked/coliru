#include <mutex>

std::mutex m;

bool the_bool;

int main() {
    std::unique_lock<std::mutex> l(m);
    if(the_bool) {
        l.unlock();
        // no mutual exclusion
    }
    // mutual exclusion
}
