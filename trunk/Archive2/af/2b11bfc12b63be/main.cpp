#include <iostream>
#include <array>

// CRTP

enum class lattice_name {
    square,
    cube,
};

template<typename T>
struct lattice {
    int num_edges() {
        return static_cast<T*>(this)->edgevectors('n');        
    }
};

struct square : lattice<square> {
    int edgevectors(const int i) {
        if (i == 'n') return 4;
        else          return -1;
    }
};

struct honeycomb : lattice<honeycomb> {
    int edgevectors(const int i) {
        if (i == 'n') return 3;
        else          return -1;
    }
};

int main(void) { 
  square A;
  std::cout << A.num_edges() << std::endl;
  honeycomb B;
  std::cout << B.num_edges() << std::endl;
}