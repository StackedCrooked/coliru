#include <vector>
using std::vector;

class Data {
  public:
    Data(int a, int b, int c) : a(a), b(b), c(c) {}

    // Removing any/all of these constructors changes nothing!
    Data& operator=(const Data& s) = default;
    Data(const Data& s) = default;
    Data(Data&& s) = default;
    ~Data() = default;

    const int a;
    const int b;
    const int c;
};


int main() {
  vector<Data> v;
  Data e(1,2,3);

  // Problem line
  v.emplace_back(4,5,6);
}