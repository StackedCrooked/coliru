#include <ctime>
#include <chrono>
#include <iostream>
#include <vector>
using namespace std;

int total = 1000000;

struct BaseClass {
    float m[16];
	int id;

	BaseClass(int _id){
		id = _id;
	}
};

int main() {

  std::vector< BaseClass > ar;

  {
    ar.reserve(total);
	auto t_start = std::chrono::high_resolution_clock::now();
    for (int var = 0; var < total; ++var) {
      ar.emplace_back(var);
    }
	auto t_end = std::chrono::high_resolution_clock::now();
	std::cout<< std::chrono::duration_cast<std::chrono::milliseconds>(t_end - t_start).count();
    ar.clear();
  }

  {
    ar.reserve(total);
    for (int var = 0; var < total; ++var) {
      ar.emplace_back(var);
    }
    ar.clear();
  }
	
	return 0;
}