#include <vector>
#include <iostream>

class A {
  private:
    std::vector<int> rep;
  public:
    std::size_t size() { return rep.size(); }
    int& operator[](std::size_t index) { return rep[index]; }
    void newmethod();

    A(size_t n, int m) : rep(n,m) {}
};

void A::newmethod() {
  for (std::size_t i=0; i < (this->size()); ++i) {
    std::cout << (*this)[i] << " ";
  }
  for (std::size_t i=0; i < (this->size()); ++i) {
    std::cout << this->operator[](i) << " "; //Causes an error!
  }
  return;
}

int main() {
  A(17,3).newmethod();
  return 0;
}