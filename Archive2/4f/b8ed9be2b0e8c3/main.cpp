#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>

int main() { 
  std::queue<int, std::vector<int>> Q;
  
  Q.push(1);
  Q.push(2);
  
  int *t = &(Q.front());
  std::for_each(t, t + Q.size(), [](int const i){ std::cout << i << " "; });
  std::cout << std::endl;
}