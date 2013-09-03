#include <thread>
#include <functional>
#include <memory>
#include <atomic>
#include <iostream>
typedef std::function<void() > CallBackToAlwaysRun;

class Active {
   CallBackToAlwaysRun callToRun;
   std::atomic<bool> keepRunning; // only needs to be atomic since we are changing it from the destructor and not the thread
   std::thread thd;
   
   void internal_run() {
      while (keepRunning) {
         callToRun();
      }
      std::cout << "\nExiting thread loop" << std::endl << std::flush;
      
   }
   
   
public:
   explicit Active(CallBackToAlwaysRun callback): callToRun(callback){ keepRunning = true;}
   
   ~Active() {
      keepRunning = false;  // must be atomic since it is not the bg thread that changes the member
      thd.join();
   }
   static std::unique_ptr<Active> createActive(CallBackToAlwaysRun callback) {
      std::unique_ptr<Active> ptr(new Active(std::move(callback))); // 1. thread container is created
      ptr->thd = std::thread(&Active::internal_run, ptr.get()); // 2. thread is creted 
      return ptr;
   }
};



#include <iostream>
#include <string>


using namespace std;
struct ThreadedHelloWorld {  
private:
   std::string name;
   std::unique_ptr<Active> backgroundPrint;

public:   
   explicit ThreadedHelloWorld(std::string nameX) : name("Hello World "){ 
      name.append(nameX); 
      
      backgroundPrint = Active::createActive([this]{printHelloWorld();});
      }
   void printHelloWorld() {
      cout << "\nHello World " << name << "\n" << flush;
   }
};

#include <chrono>
int main() {
   { 
      auto threadedObject = ThreadedHelloWorld{"John"};
      std::chrono::milliseconds dura( 200 );
      std::this_thread::sleep_for( dura );
      
   } 
   // At scope exit threadedHelloWorld will exit. Active destructor will be called and the threaded run will stop safely
}