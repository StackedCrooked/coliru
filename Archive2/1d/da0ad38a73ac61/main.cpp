#include <thread>


struct Test {
    void func(int x) {}
};


int main() {
    Test x;
    std::thread t(&Test::func, &x, 42);
    t.join();
}