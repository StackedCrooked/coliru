#include <vector>
#include <iostream>

using namespace std;

auto main() -> int
{
  // Test 1:
  {
    auto v = vector<int>{9, 9};
    auto i = 0;
    v[i++] = i++;
    cout << v[0] << v[1] << endl; // VS 2013 Debug: "19", Release: "09"
  }

  // Test 2:
  {
    auto assign = [](int& lv, int rv) { return lv = rv, lv; };
    auto inc = [](int& lv) { auto t = lv; ++lv; return t; };
     
    auto v = vector<int>{9, 9};
    auto i = 0;
    assign(v.at(inc(i)), inc(i));
    cout << v[0] << v[1] << endl; // VS 2013 Debug: "90", Release: "90"
  }
  return 0;
}