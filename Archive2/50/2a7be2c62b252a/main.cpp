#include <cassert> // assert
#include <csignal> // std::signal
#include <iostream> // std::cout
 
class Tester {
 public:
  Tester() {
    std::cout << "Tester ctor\n";
  }
 
  ~Tester() {
    std::cout << "Tester dtor\n";
  }
};
 
// Destructor not called
Tester static_tester;
 
void signal_handler(int signal) {
  if (signal == SIGABRT) {
    std::cerr << "SIGABRT received\n";
  }
  else {
    std::cerr << "Unexpected signal " << signal << " received\n";
  }
  std::_Exit(EXIT_FAILURE);
}
 
int main() {
  // Destructor not called
  Tester automatic_tester;
 
  // Setup handler
  const auto previous_handler = std::signal(SIGABRT, signal_handler);
  if (previous_handler == SIG_ERR) {
    std::cerr << "Setup failed\n";
    return EXIT_FAILURE;
  }
 
  // Raise SIGABRT
  assert(false);
 
  std::cout << "This code is unreachable\n";
  return EXIT_SUCCESS;
}