#include <iostream>
#include <vector>
#include <map>
#include <random>

double pdf( int i) { return i*1234; }

int main()
{
int n = 10;
std::vector< double> weights( n);
for( int i = 0; i < n; ++i) {
  weights[i] = pdf( i + 1);
}

std::default_random_engine generator;
std::discrete_distribution<int> distribution( weights.begin(), weights.end()) ;

std::map<int, int> m;
for(int n=0; n<10000; ++n) {
    ++m[ distribution( generator)];
}
for(auto p : m) {
    std::cout << p.first << " generated " << p.second << " times\n";
}

return 0;
}
