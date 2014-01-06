#include <iostream>
#include <thread>
#include<stdint.h>

typedef union {
  uint32_t Reg;
  struct {
    uint16_t Cx; 
    uint16_t sf; 
  };  
} tf; 

typedef struct {
  uint16_t i;
  uint16_t j;
} st; 

int bar(tf, tf);

int foo(tf t0, int32_t offset) {
  tf uoff;
  st s;
  t0.Reg = uoff.Reg + s.i + (uint32_t)offset;
  t0.sf = uoff.sf;
  return bar(t0, uoff);
}


int n1 = 0;
int n2 = 0;
struct func
{
    
    func() { n1++;}
    func(const func& _f) { n2++;}

    void operator()() {}
};

int main()
{   

    return 0;
}