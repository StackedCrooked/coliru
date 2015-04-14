#include <string>
#include <vector>
#include <iostream>
using namespace std;

struct X {
  int x = 0;
  string y;
  //X(int x, string y) : x(x), y(move(y)) {}
};

int main() {
  vector<X> vx;
  X lx(2, "test");
  cout << "lx.x: " << lx.x << endl;
  //vx.emplace_back(1, "test");
  cout << "ok" << endl;
  return 0;
}