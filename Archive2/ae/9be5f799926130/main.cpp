#include <iostream>
#include <string>
#include <vector>
#include <initializer_list>

struct duo {
  duo(const std::string key,int value) :key(key) ,value(value) {};
  const std::string key;
  int value;
};

struct Hash {
  std::vector<duo> lister;
  Hash(std::initializer_list<duo> passed) :lister(passed) {};
    };

duo operator >> (const std::string id,int value) {
  return duo(id,value);
}

int main(){
  Hash table = {"test1" >> 1};
  std::cout << table.lister[0].key << table.lister[0].value;
}
