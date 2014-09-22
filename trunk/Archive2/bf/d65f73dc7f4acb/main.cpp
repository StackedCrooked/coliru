#include <iostream>
#include <algorithm>
#include <numeric>
#include <chrono>

static auto matching_characters(std::string s1, std::string s2) {
  sort(begin(s1), end(s1));
  sort(begin(s2), end(s2));
  std::string intersection;
  std::set_intersection(begin(s1), end(s1), begin(s2), end(s2),
                        back_inserter(intersection));
  return intersection.size();
}

int main() {
  auto start = std::chrono::high_resolution_clock::now();
  auto r1 = matching_characters("assign", "assingn");
  auto r2 = matching_characters("sisdirturn", "disturb");
  auto end = std::chrono::high_resolution_clock::now();
  std::cout << r1 << '\n'; // 6
  std::cout << r2 << '\n'; // 6

  std::cout << (end - start) / std::chrono::nanoseconds(1) << "ns\n";
}

