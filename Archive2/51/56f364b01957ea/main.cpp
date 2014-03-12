#include <unordered_map>
#include <mutex>

int main() {
    std::unordered_map<int, std::mutex> m;
    std::lock_guard<std::mutex> guard(m[1]);
}
