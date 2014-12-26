#include <vector>
#include <queue>
#include <string>
using namespace std;

int main() {
  std::queue<int, std::vector<string>> Q;
  Q.push("1");
  Q.push("2");
  
  //Q.pop(); // -----> BLAST!!!
}