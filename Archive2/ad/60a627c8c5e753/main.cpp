#include <iostream>
#include <vector>
#include <string>

struct ComparisonPair {
  std::string name;
  int count;
};

int main() {
  std::vector<ComparisonPair> comparisons{{"You", 1}, {"Me", 2}};
  std::vector<ComparisonPair>::iterator i;
  for (i = comparisons.begin(); i!= comparisons.end(); ++i) {
    std::cout << i->name << " - " << i->count << std::endl;
  }
}