#include <vector>

using namespace std;

template <typename T>
class my_vec : public vector<T> {
public:
  using vector<T>::vector;
};

int main() {
  my_vec<int> v0;
  my_vec<int> v1 { 1, 2, 3, 4, 5 };
  my_vec<int> v2 ( 42 );
  my_vec<int> v3 ( v1 );
  my_vec<int> v4 ( v1.begin()+1, v1.end()-1 );
  return 0;
}