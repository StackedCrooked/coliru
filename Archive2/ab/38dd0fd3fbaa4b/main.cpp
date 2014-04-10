#include <cassert>
#include <iostream>
#include <string>

std::string create_my_device_name(unsigned int i){
  assert (0 <= i && i < 16);
  return "PZTN" + std::to_string(i) + "R3451";
}

int main(){
    for(int i{0}; i < 16; ++i)
        std::cout<<create_my_device_name(i)<<std::endl;
        
    return 0;
}