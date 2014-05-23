#include <iostream>
#include <future>

int main() {
//called_from_async launched in a separate thread if possible
  std::future<int> result(
  std::async([](int m, int n) { return m + n; }, 2, 4));

  std::cout << "Message from main." << std::endl;

//retrive and print the value stored in the future
  std::cout << result.get() << std::endl;
}
