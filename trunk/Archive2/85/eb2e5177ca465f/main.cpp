#include <iostream>
#include <iostream>
#include <thread>
//#include <unistd.h>
#include <atomic>
#include <future>

std::atomic<bool> quit_now ;

unsigned long long thread1()
{
   unsigned long long i = 0 ;
   while( !quit_now )
   {
      ++i ;
      // ::usleep(100000);
      std::this_thread::sleep_for( std::chrono::microseconds(100) ) ;
   }
   return i ;
}

void thread3()
{
      char ch = 0;
      while(1)
      {
            std::cin >> ch;
            if (ch == 'q') break;
      }
      //return;
}

int main()
{
      std::thread th1(thread1);
      std::thread th3(thread3);
      auto future = std::async( std::launch::async, thread1 ) ;
      std::this_thread::sleep_for( std::chrono::milliseconds(100) ) ;
      
      //th1.detach();
      th3.join();
      
      std::cout << "All done\n";
      quit_now = true ;
      
      th1.join() ; // wait for thread
      std::cout << "loop ran " << future.get() << " times.\n" ; // wait for fututre result
}