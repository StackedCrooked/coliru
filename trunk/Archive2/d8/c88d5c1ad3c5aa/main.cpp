#include <iostream>
#include <algorithm>
#include <numeric>
#include <chrono>

static auto matching_characters(std::string const &s1, std::string const &s2) {
  int s1_char_frequencies[256] = {};
  int s2_char_frequencies[256] = {};
  for_each(begin(s1), end(s1),
           [&](unsigned char c) { ++s1_char_frequencies[c]; });
  for_each(begin(s2), end(s2),
           [&](unsigned char c) { ++s2_char_frequencies[c]; });

  return std::inner_product(
      std::begin(s1_char_frequencies), std::end(s1_char_frequencies),
      std::begin(s2_char_frequencies), 0, std::plus<>(), [](auto l, auto r) { return std::min(l, r); });
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

