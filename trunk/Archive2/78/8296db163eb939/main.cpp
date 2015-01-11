#include <memory>
#include <vector>
#include <thread>
#include <mutex>
#include <algorithm>

using namespace std;

struct RKD {
    RKD() { // expensive
        this_thread::sleep_for(chrono::milliseconds(rand() % 100));
    }

    ~RKD() {
    }
};

int main() {
    static const int N         = 500;
    static const int ChunkSize = 100;
    std::unique_ptr<RKD[N], decltype(&::free)> rkd_buffer(static_cast<RKD(*)[N]>(::malloc(sizeof(RKD) * N)), ::free);

    vector<thread> group;
    for (int chunk = 0; chunk < N/ChunkSize; chunk += ChunkSize)
        group.emplace_back([&] { 
            for (int i=chunk * ChunkSize; i<(ChunkSize + chunk*ChunkSize); ++i)
                new (rkd_buffer.get() + i) RKD;
        });

    for (auto& t:group) if (t.joinable()) t.join();
}
