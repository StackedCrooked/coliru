#include <functional> // bind
#include <iostream>
#include <vector>
#include <random>

namespace {
  std::random_device generate_seed;
  std::mt19937 eng(generate_seed());    
  class Cycles {
    int line;
    std::normal_distribution<> rand_norm;
    std::function<double()> r_norm;
  public:
    Cycles(): line(0), rand_norm(0.85, 0.05), r_norm(std::bind(rand_norm, eng))
    {
      // print distribution
      std::vector<size_t> freq(200);
      for (int i = 0; i < 900; ++i) ++freq.at(std::round(r_norm()*100));

      size_t line = 0, max_line = freq.size()-1;
      for ( ; not freq[line] and line <= max_line;  ++line);
      for ( ; not freq[max_line] and max_line >= line; --max_line);
      for ( ; line <= max_line; ++line) {
        std::cout << line << '\t';
        for (size_t j = 0; j < freq[line]; ++j) std::cout << '*';
        std::cout << std::endl;
      }
    }
  };
}    
int main() {
  Cycles c;
}