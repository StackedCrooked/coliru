    #include <chrono>
    #include <iostream>
    #include <vector>
    #include <functional>
    #include <thread>
    #include <future>

    typedef std::chrono::high_resolution_clock::duration duration;
    typedef std::chrono::high_resolution_clock::time_point time_point;
    typedef std::vector<std::pair<duration, std::function< void() >>> delayed_task_list;

    void do_delayed_tasks( delayed_task_list list ) {
      time_point start = std::chrono::high_resolution_clock::now();
      time_point last = start;
      for (auto&& task: list) {
        time_point next = last + task.first;
        duration wait_for = next - std::chrono::high_resolution_clock::now();
        std::this_thread::sleep_for( wait_for );
        task.second();
        last = next;
      }
    }
    std::future<void> execute_delayed_tasks_in_order_elsewhere( delayed_task_list list ) {
      return std::async( std::launch::async, do_delayed_tasks, std::move(list) );
    }
    int main() {
      delayed_task_list meh;
      meh.emplace_back( duration(), []{ std::cout << "hello world\n"; } );
      std::future<void> f = execute_delayed_tasks_in_order_elsewhere( meh );
      f.wait(); // wait for the task list to complete: you can instead store the `future`
    }
