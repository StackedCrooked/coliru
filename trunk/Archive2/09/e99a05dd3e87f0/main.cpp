#include <algorithm>
#include <cstdlib>
#include <functional>
#include <string>
#include <iostream>
#include <iterator>
#include <random>

unsigned
dist(std::string const& s, std::string const& target) {
  unsigned result{};
  for (std::size_t i = 0; i < s.size(); ++i)
    result += std::abs(s[i] - target[i]);
  return result;
}

int
main() {
  std::string const target = "mmorpg";
  std::string const range = "abcdefghijklmnopqrstuvwxyz0123456789*/+-,.";
  std::default_random_engine prng;
  std::uniform_int_distribution<std::size_t> 
    rnd_index_distrib(0, target.length()),
    rnd_letter_distrib(0, range.length());
  auto rnd_char  = [&] { return range[rnd_letter_distrib(prng)]; };
  auto rnd_index = std::bind(rnd_index_distrib, std::ref(prng));
  
  std::string s, t;
  std::generate_n(std::back_inserter(s), target.length(), rnd_char);
  unsigned s_dist = dist(s, target);
  unsigned long long tries{};

  while (s_dist != 0) {
    t = s;
    t[rnd_index()] = rnd_char();
    unsigned const t_dist = dist(t, target);
    if (t_dist < s_dist) {
      s = t;
      s_dist = t_dist;
    }

    ++tries;
  }

  std::cout << s << " in " << tries << " tries\n";
}

