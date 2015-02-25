// ConsoleApplication6.cpp : Defines the entry point for the console application.
//

#include <iostream>

#include <memory>
#include <thread>
#include <vector>
#include <atomic>

int main()
{
  auto ptr = std::make_shared<int>(10);

  bool run = true;
  std::thread t1([&] {
    while (run)
    {
      ptr = std::make_shared<int>(10);
    }
  });

  std::vector<std::thread> thrs;
  for (int i = 0; i < 10; ++i)
  {
    std::thread t([&] {
      while (run)
      {
        auto tmp = ptr;
        (void)tmp;
      }
      });
    thrs.push_back(std::move(t));
  }

  char c;
  std::cin >> c;
}

