#include <future>
#include <iostream>

struct FFT {
  FFT (int val) : value (val) { }
  
  int get_value () {
    return value;
  }
  
  int value;
};

int
main (int argc, char *argv[])
{
  FFT * ptr = new FFT (123);
  
  auto result = std::async (&FFT::get_value, ptr);
  
  std::cout << result.get () << std::endl;
  
  delete ptr;
}
