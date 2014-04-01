#include <thread>

int func;

int main() {
    std::thread t;
    t = std::thread(func);
}
