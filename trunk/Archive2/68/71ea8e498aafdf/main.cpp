#include <iostream>
#include <vector>

using namespace std;

static void func1(vector<int> &v) {
  // This function can modify "v"
  for (auto &i : v) {
    i = 0;
  }
}

static void func2(vector<int> const &v) {
  // This function can only read from "v"
  for (auto &i : v) {
    i = 0;
  }
}

int main(int argc, const char *argv[]) {
  vector<int> v;
  v.push_back(5);
  v.push_back(10);
  func1(v);
  func2(v);
}
