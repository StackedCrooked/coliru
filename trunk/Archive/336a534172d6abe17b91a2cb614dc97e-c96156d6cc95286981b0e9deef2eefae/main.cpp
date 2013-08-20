#include <bitset>
using namespace std;

bitset<96> bitset_to_string(bitset<32> addr, bitset<64> wdata)
{return bitset<96>{addr.to_string<char>() + wdata.to_string<char>()};}

template<size_t N1, size_t N2>                                                                      
std::bitset<N1+N2> bitwise_copy(std::bitset<N1> addr, std::bitset<N2> wdata) {             
  std::bitset<N1+N2> res;                                                                           
  for(size_t k=0; k<N2; k++) {                                                                      
    res[k] = wdata[k];                                                                                 
  }                                                                                                 
  for(size_t k=0; k<N1; k++) {                                                                      
    res[N2+k] = addr[k];                                                                              
  }                                                                                                 
  return std::move(res);                                                                            
}     
template<size_t N1, size_t N2>                                                             
std::bitset<N1+N2> bitwise_copy2(bitset<N1> addr, bitset<N2> wdata) {             
  std::bitset<N1+N2> res;                                                                           
  for(size_t k=0; k<N2; k++)   
    res.set(k, wdata[k]);                                                                           
  for(size_t k=0; k<N1; k++) 
    res.set(N2+k, addr[k]);                                                                           
  return res;                                                                            
}   

#include <iostream>
#include <ctime>
#include <iomanip>
template<class Func>
void test(const char* name, Func func) {
    clock_t begin = clock();
    bitset<96> res=0;
    bitset<32> addr = 0xabcdef01;
    bitset<64> wdata = 0xabcdef0123456789;
    for(unsigned i=0; i<1000000; ++i)
        res = func(addr, wdata);
    clock_t end = clock();
    std::cout << std::setw(16) << name;
    std::cout << " ticks:" << std::setw(10) << (end-begin);
    std::cout << " result:" << res[0];
    std::cout << '\n';
}

int main() {
    test("bitset_to_string", bitset_to_string);
    test("bitset_to_string", bitset_to_string);
    test("bitset_to_string", bitset_to_string);
    test("bitwise_copy", bitwise_copy<32,64>);
    test("bitwise_copy", bitwise_copy<32,64>);
    test("bitwise_copy", bitwise_copy<32,64>);
    test("bitwise_copy2", bitwise_copy2<32,64>);
    test("bitwise_copy2", bitwise_copy2<32,64>);
    test("bitwise_copy2", bitwise_copy2<32,64>);
    test("bitset_to_string", bitset_to_string);
    test("bitset_to_string", bitset_to_string);
    test("bitset_to_string", bitset_to_string);
    test("bitwise_copy", bitwise_copy<32,64>);
    test("bitwise_copy", bitwise_copy<32,64>);
    test("bitwise_copy", bitwise_copy<32,64>);
    test("bitwise_copy2", bitwise_copy2<32,64>);
    test("bitwise_copy2", bitwise_copy2<32,64>);
    test("bitwise_copy2", bitwise_copy2<32,64>);
}
