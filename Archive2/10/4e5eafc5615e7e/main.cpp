#include <stdio.h>
#include <thread>
#include <unistd.h>

void m ()
{

  int a(0), b(0);

  auto f = [&]() 
    {
      while (1)
      { 
          __transaction_atomic
          {
            a++;
            b++;
          };
      }
    };

  
  std::thread(f).detach();

  std::thread([&]{ while(1) { if ( __transaction_atomic(a-b) != 0 ) { printf("error\n"); exit(0); } } }).detach();
  std::thread([] { sleep(1); printf("no errors\n"); exit(0); }).detach();
  sleep(2);
  printf("exit\n");
  return;



}

int main ()
{
  m();
  printf("hi\n");
}
