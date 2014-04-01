#include <thread>

int func;

int main() {
    std::thread t(func);
}
