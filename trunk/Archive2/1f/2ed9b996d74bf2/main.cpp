#include <algorithm>
#include <iostream>
#include <iterator>
#include <utility>
#include <vector>
using namespace std;

class StrangeComparison {
public:
  StrangeComparison(const vector<int>& ordering) : ordering_(ordering) {}
  bool operator()(int a, int b) const {
    auto index_a = find(ordering_.begin(), ordering_.end(), a);
    auto index_b = find(ordering_.begin(), ordering_.end(), b);
    return make_pair(index_a, a) < make_pair(index_b, b);
  }
private:
  const vector<int>& ordering_;
};

int main() {
   vector<int> v{5,4,1,2};
   vector<int> v2{2,4,3,5,1,6,8,7};
   vector<int> v3{1,4,2,3};

   sort(v2.begin(), v2.end(), StrangeComparison(v));
   copy(v2.begin(), v2.end(), ostream_iterator<int>(cout, ", "));
   cout << endl;

   sort(v3.begin(), v3.end(), StrangeComparison(v));
   copy(v3.begin(), v3.end(), ostream_iterator<int>(cout, ", "));
   cout << endl;
}