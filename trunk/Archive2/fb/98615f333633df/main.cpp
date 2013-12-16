#include <mutex>
#include <thread>
#include <vector>
#include <iostream>

std::mutex io_lock;

thread_local int a = 0;

void set () {
  thread_local static int val = 0;

  a = ++val;
}

void reset () {
  a = 0;
}

void print () {
  std::lock_guard<std::mutex> _ (io_lock);

  std::cerr << std::this_thread::get_id () << " -> " << a << "\n";
}

int
main (int argc, char *argv[])
{
  std::vector<std::thread> vec;

  std::thread t1 ([]{ set (); reset (); set (); print (); });
  std::thread t2 ([]{ set ();                   print (); });

  for (auto p : { &t1, &t2 })
    p->join ();

  print ();
}
