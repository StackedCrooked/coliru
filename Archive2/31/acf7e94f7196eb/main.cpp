#include <vector>



int main(){
  std::vector<int> x;
for (int j = 0; j <= 1000000; ++j) // fill with values from [0..10^6]
    x.push_back(j);

long long equation = x[50000] * x[50000] * x[50000] + 3 * x[50000] - 14; 
    return 0;
}