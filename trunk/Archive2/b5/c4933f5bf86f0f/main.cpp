#include <iostream>
#include <future>
#include <thread>
#include <chrono> 
int main() {
   std::packaged_task<std::string()> task([]() { return "Hello from the past";} ); 
   std::future<std::string> result = task.get_future(); 
   std::thread(std::move(task)).detach(); 
   std::cout << "Waiting for past to catch up ...";

   result.wait();
   std::cout << "Done!\nThe message : '" << result.get() << "' \n";
}