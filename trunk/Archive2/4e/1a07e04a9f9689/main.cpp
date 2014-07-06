#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>

template<class T, class Alloc = std::allocator<T>>
class queuevec : public std::vector<T, Alloc> {
public:
  void pop_front() {
   if(!this->empty()) this->erase(this->begin());
  }
};

int main() { 
  std::queue<int, queuevec<int>> Q;
  
  for(int i(0); i < 10; ++i) Q.push(i);
  
  Q.pop();
  
  int *t = &(Q.front());
  std::for_each(t, t + Q.size(), [](int const i){ std::cout << i << " "; });
  std::cout << std::endl;
}