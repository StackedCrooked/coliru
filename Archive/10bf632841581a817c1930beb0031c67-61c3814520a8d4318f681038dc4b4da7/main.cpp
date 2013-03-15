#include <condition_variable>
#include <thread>
#include <vector>

int main() {
    for (int i = 0; i != 20; ++i) {
        std::thread([]() {
            try {
                std::vector<long> vec(1);
                for (;;) {
                    vec.resize(vec.size() * 2);
                }
            }
            catch (...)
            {
            }
        }).detach();
    }
    std::this_thread::sleep_for(std::chrono::seconds(10));
}
