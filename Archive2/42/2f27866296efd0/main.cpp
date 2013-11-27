#include <stdlib.h> // EXIT_SUCCESS
#include <iostream> // std::cout
#include <thread>
#include <cassert> // assert
#include <system_error>

std::thread* global_thread = nullptr;

void job() {
  std::this_thread::sleep_for(std::chrono::seconds(1)); // sync HACK
  assert(global_thread);
  std::cout << "joinable: " << global_thread->joinable() << std::endl;
  try {
    global_thread->join();
    std::cout << "join succeed" << std::endl;
  }
  catch(std::system_error& error) {
    std::cout << "catched: " << error.what() << std::endl;
  }
}

int main() {
  std::thread thread(job);
  global_thread = &thread;
  thread.join();
  return EXIT_SUCCESS;
}