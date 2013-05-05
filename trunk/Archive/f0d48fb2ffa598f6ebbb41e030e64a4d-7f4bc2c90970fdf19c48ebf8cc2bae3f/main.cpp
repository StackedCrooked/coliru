#include <iostream>
        #include <atomic>
        #include <thread>
 
        std::atomic<int>    last(2);
        std::atomic<int>    last_Value(0);
        std::atomic<bool>   running(true);
 
        void function_Thread_1()
        {
                  while(running)
                  {
                          if(last == 2)
                          {
                                  last_Value = last_Value + 1;
                                  std::cout << last_Value << std::endl;
                                  last = 1;
                          }
                  }
        }
 
        void function_Thread_2()
        {
                  while(running)
                  {
                          if(last == 1)
                          {
                                  last_Value = last_Value + 1;
                                  std::cout << last_Value << std::endl;
                                  last = 2;
                          }
                  }
        }
 
        int main() 
        {
                std::thread a(function_Thread_1);
                std::thread b(function_Thread_2);
 
                while(last_Value != 6){}//we want to print 1 to 6
 
                running = false;//inform threads we are about to stop
 
                a.join();
                b.join();//join
                return 0;
        }