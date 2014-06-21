#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct One {
  string name;
  vector<string> values;
};

struct Two {
  string name;
  vector<One> one_values;

  bool operator<(const Two& other) const
  {
      return name < other.name;
  }
};

int main() {
   vector<Two> twos;
   std::sort(twos.begin(), twos.end());
}
