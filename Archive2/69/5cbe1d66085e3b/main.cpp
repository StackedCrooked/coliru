#include<iostream>
#include<vector>

int main() {
  std::vector<std::string> vec;
  for(int i=0; i!=7; ++i) {
    std::string buffer;
    if(i%2==0) {
      buffer = "hello";
    } else {
      buffer = "bye";
    }
    vec.push_back(buffer);
  }
  for(auto message : vec) {
    std::cout<< message << "\n";
  }
}
