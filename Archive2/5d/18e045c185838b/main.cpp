#include <vector>
#include <thread>
#include <stdlib.h>
#include <iostream>
#include <cstdint>

//#define numEntries 100
class CAS
{
private:
std::vector <std::thread> threads;
long tagIndex,arg_tag;
public:

struct vtable
{
  long tag;
};

std::vector<vtable> vt;

CAS(int numEntries)
{
  vt.resize(numEntries);
}

void pSearch(int i)
{
 int a=10;

  //unsigned i= *((unsigned *)thInd);  

  //if(arg_tag==vt[i].tag)
  //tagIndex=i;
}

void CAS_threadEND(int i)
{
threads[i].join();
}

void parallelSearchINIT(unsigned numEntries, int _tag)
{
  //threads.resize(numEntries);
  for(unsigned i=0;i<numEntries;i++)
      {
    arg_tag=_tag;
    threads.push_back(std::thread (CAS::pSearch,i));



    // t;
    //(void (A::*)(int)) &A::pSearch

  }


}




};

int main()
{

int _tag=11;
unsigned numEntries=100;
CAS c(numEntries);
c.parallelSearchINIT(numEntries,_tag);

for(unsigned i=0;i<numEntries;i++)
c.CAS_threadEND(i);



}