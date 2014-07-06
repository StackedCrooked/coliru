#include <vector>
#include <queue>

int main() {
  std::queue<int, std::vector<int>> Q;
  Q.push(1);
  Q.push(2);
  
  Q.pop(); // -----> BLAST!!!
}