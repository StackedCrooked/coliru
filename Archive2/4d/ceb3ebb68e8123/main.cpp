#include <iostream>
#include <bitset>

int main(){
     auto binary =0b0110111;
     auto binary2=0b0101100;
     auto sum=binary+binary2;
     std::cout<<std::bitset<7>(binary)<<'\n'; 
     std::cout<<std::bitset<7>(binary2)<<'\n'; 
     std::cout<<std::bitset<7>(sum); 
}
