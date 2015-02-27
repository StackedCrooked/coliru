#include <atomic>
#include <iostream>
#include <mutex>
#include <random>
#include <thread>
#include <unordered_map>
#include <utility>

struct Point
{
  int x, y, z;
};

struct Data
{
  std::atomic<int> version;
  std::atomic<Point> point;
};

std::unordered_map<std::string, Data> hashtable; // global
std::mutex mtx;

Data& lookup(const std::string& key) {
  std::lock_guard<std::mutex> guard{mtx};
  return hashtable[key];
}

std::pair<std::string, Point> get_new_stuff();
void process_point(int, const Point&);

void thread1() {
  std::string key;
  Point point;
  std::tie(key, point) = get_new_stuff();
  auto& ref = lookup(key);
  ref.point.store(point, std::memory_order_relaxed);
  ref.version.fetch_add(1, std::memory_order_release);
}

void thread2() {
  auto& ref = lookup("string1");
  int local_version = 0;
  for (;;) {
    auto const version = ref.version.load(std::memory_order_acquire);
    if (local_version != version) {
      auto point = ref.point.load(std::memory_order_relaxed);
      if (version == ref.version.load(std::memory_order_acquire)) {
        local_version = version;
        process_point(version, point);
      }
    }
  }
}

std::atomic<bool> finished{false};
static constexpr int n = 20;

std::pair<std::string, Point> get_new_stuff() {
    static std::mt19937 engine{std::random_device{}()};
    std::uniform_int_distribution<> dist{1, 100};
    return {"string1", Point{dist(engine), dist(engine), dist(engine)}};
}

void process_point(int version, const Point& point) {
    static int counter;
    std::cout << version << ": {" << point.x << ", " << point.y << ", " << point.z << "}\n";
    if (++counter >= n) {
        finished = true;
        throw 1;
    }
}

int main() {
    std::thread t2{[]{
        try { thread2(); } catch(int&) {}
    }};
    std::thread t1{[]{
        while (!finished) {
          thread1();
        }
    }};
    t2.join();
    t1.join();
}
