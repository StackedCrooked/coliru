#include <omp.h>
#include <array>
#include <iostream>

constexpr int max_dim = 4;

using tx = std::array<int, max_dim>;

class grid {
  public:    
  grid(const tx ilength) 
  : f_length(ilength),
    f_size(calculate_size(ilength)) {;}
  tx length(void) const {
    return f_length;
  }
  int length(const int i) const {
    return f_length[i];
  }
  int size(void) const {
    return f_size;
  }
  int index(const tx x) const {    
    return  x[0]
          + x[1] * length(0)
          + x[2] * length(0) * length(1)
          + x[3] * length(0) * length(1) * length(2);
  }
  tx coordinates(const int xi) const {
    tx  tmp1;
    int tmp2 = 1;
    for (int i = 0; i < f_length.size(); i++) {
      tmp1[i] = (xi / length(i)) % tmp2;
      tmp2 *= length(i);
    }
    return tmp1;
  } 
  int hop(const int dx, const int x, const int xmax) const {
    return (dx < 0 ? (x + dx + xmax * (x < -dx)) 
                   : (x + dx - xmax * (x > xmax - 1 - dx)));
  }
  tx hop(const tx dx, const tx x) const {
    return {hop(dx[0], x[0], length(0)),
            hop(dx[1], x[1], length(1)),
            hop(dx[2], x[2], length(2)),
            hop(dx[3], x[3], length(3))};
  }
  private:
  int calculate_size(const tx ilength) {
    int tmp = 1;
    for (int i = 0; i < ilength.size(); i++) {
      tmp *= ilength[i];
    }
    return tmp;
  }
  const tx  f_length;
  const int f_size;
};

int main(void) {
    grid A({10,10,10});
    int sum = 0;
    double start = omp_get_wtime();
    for(int i = 0; i < 10000; i++) {
        for (int j = 0; j < A.size(); j++) {
            sum += A.coordinates(j)[0];    
        }
    }
    double end = omp_get_wtime();
    std::cout << std::scientific << end - start << "\t" << sum << std::endl;
    auto x = A.index({1,2,3});
    std::cout << x[0] << std::endl;
}