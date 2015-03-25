#include <pthread.h>
#include <unistd.h>
#include <sched.h>
#include <string.h>

#include <chrono>
#include <iostream>
#include <memory>


int shared_i = 0;

void* shared_i_increment(void* arg)
{
 shared_i++; 
 return nullptr;
}


int main(int argc,char* argv[],char* env[])
{
  constexpr size_t thread_count = 100000;
  constexpr size_t fake_stack_size = 16384;
  constexpr size_t true_stack_size = 16384;
  constexpr size_t full_stack_size = true_stack_size * thread_count + fake_stack_size;
  
  std::unique_ptr<unsigned char[]> stack(new unsigned char[full_stack_size]);
  unsigned char* stack_pointer = stack.get();
  
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  
  pthread_attr_setguardsize(&attr,0) ;
  
  pthread_t list[thread_count];
  
  std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
  size_t args[thread_count];
  for (size_t ix = 0; ix < thread_count; ix++)
  {
    pthread_attr_setstack(&attr,(void*)stack_pointer,fake_stack_size);   
    pthread_create(&list[ix], &attr, shared_i_increment,&args[ix]);
    stack_pointer += true_stack_size;
  }
  
  for (size_t ix = 0; ix < thread_count; ix++)
    pthread_join(list[ix], nullptr);
  
  std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
  std::cerr << "time in ms: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
  std::cerr << shared_i << std::endl;
  
  
}
