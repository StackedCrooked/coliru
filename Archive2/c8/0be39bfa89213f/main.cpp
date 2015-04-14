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
  auto x = X{1, "test"};
  vx.emplace_back(move(x));
  cout << "ok" << endl;
  return 0;
}