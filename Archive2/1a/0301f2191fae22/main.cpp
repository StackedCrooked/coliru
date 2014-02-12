#include <iostream>
#include <future>
#include <vector>
#include <cassert>
 
struct S {
    bool on_main_thread = false;
    int tasks_run_on_this_thread = 0;
 
    S() { std::cerr << "S ctor\n"; }
    ~S() { std::cerr << "S dtor\n"; }
};
 
thread_local S s;
 
int main()
{
  s.on_main_thread = true;
 
  std::vector<std::future<void>> v;
 
  const int task_count = 10;
  for (int i=0; i<task_count; ++i) {
    v.emplace_back(std::async([] {
      assert(s.tasks_run_on_this_thread == 0 || s.on_main_thread);
      ++s.tasks_run_on_this_thread;
    }));
  }
                   
  for (auto &&t : v) {
    t.get();  
  }
  std::cout << "Tasks run asynchronously: " << task_count - s.tasks_run_on_this_thread << " (Should be this many + 1 ctors/dtors run)\n";
}