#include <memory>
#include <algorithm>
#include <map>
#include <vector>
#include <functional>
#include <iostream>

using namespace std;
using namespace std::placeholders;    

shared_ptr<int> _2nd(const pair<int, shared_ptr<int>>& x) { return x.second; }

int main(){
  map<int, shared_ptr<int>> container;
  container[5] = make_shared<int>(7);

  for (int i = 0; i < 10; ++i) {
    vector<shared_ptr<int>> vec(container.size());

//    transform(container.begin(), container.end(), vec.begin(), [](pair<int, shared_ptr<int>> x) { return x.second; });
    transform(container.begin(), container.end(), vec.begin(), bind(&_2nd, _1));
    
    for( auto& x: vec ) std::cout << *x << std::endl;
  }
  
}
