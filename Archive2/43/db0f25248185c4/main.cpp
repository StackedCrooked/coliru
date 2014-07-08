#include<vector>
#include <utility>

using std::vector;

template <typename T, typename E = typename std::remove_reference<T>::type>
std::vector<E> attach_1(std::vector<E> xs, T&& x) {
  xs.push_back(std::forward<T>(x));
  return xs;
}

template <typename T>
std::vector<typename std::remove_reference<T>::type> attach_2(std::vector<typename std::remove_reference<T>::type> xs, T&& x) {
  xs.push_back(std::forward<T>(x));
  return xs;
}

int main() { 
    long V = 0L;
    vector<int> v;
    attach_1(v, V);
    attach_2(v, V);
}