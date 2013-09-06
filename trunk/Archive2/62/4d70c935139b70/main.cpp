#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

using namespace std;

int main() {
  mutex m;
  condition_variable c;

  bool fired = false;
  int i = 0;

  // This thread counts the times the condition_variable woke up.
  // If no spurious wakeups occur it should be close to 5.
  thread t([&]() {
    unique_lock<mutex> l(m);
    while (!fired) {
      c.wait_for(l, chrono::milliseconds(100));
      ++i;
    }
  });

  // Here we wait for 500ms, then signal the other thread to stop
  this_thread::sleep_for(chrono::milliseconds(500));
  {
    unique_lock<mutex> l(m);
    fired = true;
    c.notify_all();
    cout << "\n\n\n" << i << endl;
  }
  t.join();
}
