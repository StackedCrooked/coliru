#include <type_traits>
#include <utility>
#include <random>
#include <algorithm>
#include <iterator>
#include <vector>
#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <cmath>

namespace fm {
    namespace rand {
		std::minstd_rand& engine()
		{
			static std::random_device rd;
			static std::minstd_rand engine{rd()};
		
			return engine;
		}
		int d(int sides, int times) {
			static std::uniform_int_distribution<int> dist{1, sides};
			std::vector<int> v(times, 0);

			std::generate(begin(v), end(v), [] { return dist(engine()); });
			return std::accumulate(std::begin(v), std::end(v), 0);
		}
		inline int d4(int n) { return d(4, n); }
		inline int d6(int n) { return d(6, n); }
		inline int d8(int n) { return d(8, n); }
		inline int d10(int n) { return d(10, n); }
		inline int d12(int n) { return d(12, n); }
		inline int d20(int n) { return d(20, n); }

		namespace literals {
			auto operator "" d4(unsigned long long n) { 
				return [n] { return d4(n); }; 
			}
			auto operator "" d6(unsigned long long n) { 
				return [n] { return d6(n); }; 
			}
			auto operator "" d8(unsigned long long n) { 
				return [n] { return d8(n); }; 
			}
			auto operator "" d10(unsigned long long n) { 
				return [n] { return d10(n); }; 
			}
			auto operator "" d12(unsigned long long n) { 
				return [n] { return d12(n); }; 
			}
			auto operator "" d20(unsigned long long n) { 
				return [n] { return d20(n); }; 
			}
		}
	}
}

int main() {
    using namespace fm::rand::literals;
    
    std::map<int, int> hist;
    for (int n = 0; n < 30000; ++n) {
        ++hist[4d4()];
    }
    for (auto p : hist) {
        std::cout << std::fixed << std::setprecision(1) << std::setw(2)
                  << p.first << ' ' << std::string(p.second/200, '*') << '\n';
    }
    return 0;
}
