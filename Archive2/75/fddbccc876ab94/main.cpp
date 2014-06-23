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
};

bool operator<(const Two& lhs, const Two& rhs)
{
    return lhs.name < rhs.name;
}

int main() {
   vector<Two> twos;
   std::sort(twos.begin(), twos.end());
}
