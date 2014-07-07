#include<vector>
#include <utility>

using std::vector;

template <class T>
vector<T>&& id2(vector<T>&& v) {
  return std::move(v);
}

int main() { 
    std::vector<int> v(1000);
    v = id2(std::move(v));
    return v.size();
}