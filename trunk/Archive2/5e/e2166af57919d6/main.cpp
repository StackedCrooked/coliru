#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

class A {
public:
  explicit A(int i): m_i(i) {};
  explicit A(const A& other): m_i(other.m_i) {};
  A(A&& other) : m_i(other.m_i) {};
  A& operator=(A&& other) { m_i = other.m_i; return *this;}
  
  int i() const {return m_i;};
private:
  int m_i;
};

bool is_less(const A& a, const A& b) {
  return a.i() < b.i();
}

int main(int, char*[]) {
  std::vector<A> objects;
  objects.push_back(A(3));
  objects.push_back(A(5));
  objects.push_back(A(-1));

  std::cout << is_less(objects[1], objects[2]);
  std::sort(objects.begin(), objects.end(), is_less);

  for (auto& a: objects) {
    std::cout << a.i() << " ";
  }
  std::cout << std::endl;
}