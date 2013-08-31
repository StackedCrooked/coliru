// kapitel07/7_10a/move01.cpp
#include <iostream>
#include <vector>
#include <random>

class Zufallszahlen {
  int *zahlen{nullptr};
  int n{0};
public:
  Zufallszahlen(int _n, int range) : zahlen(new int[_n]),n(_n){
     std::random_device rn;
     std::mt19937 engine(rn());
     std::uniform_int_distribution<int> dice(1, range);
     for(int i=0; i < _n; ++i) {
        zahlen[i] = dice(engine);
      }
  }
  ~Zufallszahlen() {
    delete[] zahlen;
  }
  Zufallszahlen(const Zufallszahlen&) = delete;
  Zufallszahlen& operator=(const Zufallszahlen&) = delete;

  Zufallszahlen(Zufallszahlen&& a) : zahlen(std::move(a.zahlen)), n(std::move(a.n)) {
    a.zahlen=nullptr;
    a.n=0;
  }
  Zufallszahlen& operator=(Zufallszahlen &&a) {
    n = std::move(a.n);
    a.n=0;
    delete[] zahlen;
    zahlen=std::move(a.zahlen);
    a.zahlen = nullptr;
    return *this;
  }
  void print_All() {
      for(int i=0; i<n; ++i)  {
        std::cout << zahlen[i] << std::endl;
      }
    }
};

int main() {

  Zufallszahlen lottozahlen{6, 49};
  std::vector<Zufallszahlen> zvec;

  zvec.push_back(std::move(lottozahlen)); 
  zvec.emplace_back( 3, 5 );
  zvec.push_back(Zufallszahlen{6, 10});

  for( auto &it : zvec ) {
    it.print_All();
  }
}