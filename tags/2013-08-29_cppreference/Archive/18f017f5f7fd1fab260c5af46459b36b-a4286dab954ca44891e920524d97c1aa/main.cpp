#include <iostream>
#include <vector>
#include <array>
#include <list>
#include <type_traits>

struct Uniform {
    public:
        template<class container_t>
    	typename std::enable_if<std::is_same<typename container_t::value_type, float>::value>::type
		operator=(container_t& cont) {
			std::cout << "container of float\n";
            for(auto i : cont) {
                std::cout << i << "\n";
            }
		}
    	template<class container_t>
		typename std::enable_if<std::is_same<typename container_t::value_type, double>::value>::type
		operator=(container_t& cont) {
			std::cout << "container of double\n";
			for(auto i : cont) {
				std::cout << i << "\n";
			}
		}
		void operator=(std::vector<double>& cont) {
			std::cout << "Specialization of vector of double\n";
			for(auto i : cont) {
				std::cout << i << "\n";
			}
		}
		void operator=(std::array<float, 2>& cont) {
			std::cout << "Specialization of array<2> of float\n";
			for(auto i : cont) {
				std::cout << i << "\n";
			}
		}
};

int main() {
    Uniform u;
    std::list<float> test1 = {1.0, 2.0, 3.0, 4.0};
    std::vector<double> test2 = {5.0, 6.0, 7.0, 8.0};
    std::array<float, 2> test3 = {9.0, 10.0};
    u = test1;
    u = test2;
    u = test3;
    return 0;
}
