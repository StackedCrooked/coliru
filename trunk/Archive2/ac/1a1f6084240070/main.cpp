#include <iostream>
#include <thread>

class BackgroundTask {
public:
  BackgroundTask() {
    std::cout << "BackgroundTask()\n";
  }
  BackgroundTask(const BackgroundTask&) {
    std::cout << "BackgroundTask(const BackgroundTask&): " << std::hash<std::thread::id>()(std::this_thread::get_id()) << '\n';
  }
  void operator()() const {
    std::cout << "void operator()(): "  << std::hash<std::thread::id>()(std::this_thread::get_id()) << '\n';
  }
};

int main() {
  std::thread t{BackgroundTask{}};
  t.join();
}
