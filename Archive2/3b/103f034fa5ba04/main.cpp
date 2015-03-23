#include<iostream>
#include<regex>

int main(){
  std::regex regex("one|two|three|four");
  std::vector<std::string> candidates = {"one", "two", "three", "four", "five"};

  for(auto it : candidates){
    if(std::regex_match(it, regex)){
      std::cout << it << " matches regex " << std::endl;
    }
  }
}