    #include <chrono>
    #include <iostream>
    #include <vector>
    #include <functional>
    #include <thread>
    #include <future>

    typedef std::chrono::high_resolution_clock::duration duration;
    typedef std::chrono::high_resolution_clock::time_point time_point;
    typedef std::vector<std::pair<duration, std::function< void() >>> delayed_task_list;

void do_delayed_tasks( delayed_task_list list ) 
{
      time_point start = std::chrono::high_resolution_clock::now();
      time_point last = start;
      
      for (auto&& task: list) 
      {
        time_point next = last + task.first;
        
        //duration wait_for = next - std::chrono::high_resolution_clock::now();
        //duration wait_for = std::chrono::high_resolution_clock::now();

       task.second();

        //std::chrono::seconds dura( 480 );
        //std::this_thread::sleep_for( dura );
        
        //std::this_thread::sleep_for(wait_for);
        //task.second();
        last = next;
      }
}
    
std::future<void> execute_delayed_tasks_in_order_elsewhere( delayed_task_list list ) 
{
      return std::async( std::launch::async, do_delayed_tasks, std::move(list) );
}

void hello1()
{
 //std::cout << "Hello Jason" << std::endl;

   std::cout << "Growing Timer Started" << std::endl;

   auto start = std::chrono::high_resolution_clock::now();
   std::this_thread::sleep_until(start + std::chrono::seconds(10));

   std::cout << "Growing Timer Finished..." << std::endl;


}

void hello2()
{
   //for (int i=0; i<10000000; i++)
   //{
   //   std::cout << "i: " << i << std::endl;
      //std::cout << "i: " << i << std::endl;
   //}

   std::cout << "Harvested Timer started... " << std::endl;

   auto start = std::chrono::high_resolution_clock::now();
   std::this_thread::sleep_until(start + std::chrono::seconds(10));

   std::cout << "Harvested Timer finished..." << std::endl;
}

void hello3()
{
 std::cout << "Hello Tommy Refenes-------" << std::endl;
}

void hello4()
{
 std::cout << "Hello Annette----------" << std::endl;
}

int main() 
{
      delayed_task_list meh;

      meh.emplace_back( duration(), []{ std::thread t1(hello1); t1.join(); } );
      meh.emplace_back( duration(), []{ std::thread t1(hello2); t1.join(); } );
      //meh.emplace_back( duration(), []{ std::thread t1(hello3); t1.detach(); } );
      //meh.emplace_back( duration(), []{ std::thread t1(hello4); t1.detach(); } );

      //meh.emplace_back( duration(), []{ std::cout << "hello world---------------\n"; } );
      //meh.emplace_back( duration(), []{ std::cout << "hello world 2---------------\n"; } );
      //meh.emplace_back( duration(), []{ std::cout << "hello world 3---------------\n"; } );

      //meh.emplace_back( duration(), []{ std::thread t1(hello); t1.detach(); } );

      std::future<void> f = execute_delayed_tasks_in_order_elsewhere( meh );
      
      f.wait(); // wait for the task list to complete: you can instead store the `future`

      //for (int i=0; i<10000000; i++)
      //{
      //  std::cout << "i: " << i << std::endl;
      //  std::cout << "i: " << i << std::endl;
      //}
    
}


