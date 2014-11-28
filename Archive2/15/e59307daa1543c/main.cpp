#include "lotto.hpp"
#include<random>
#include<algrorithm>
#include<iostream>

using namespace std;

Ziehung::Ziehung()
{
  random_device rn;
  mt19937 engine(rn());
  uniform_int_distribution<unsigned int> lz(1,49);
  
  for(auto i=0; i<=5; ++i)
  {
    do
    {
      lottozahl[i]=lz(engine);
    }while(!gezogen(i)); // die hatte ich falschrum
   
  }
  
  std::sort(lottozahl.begin(), lottozahl.end());
} // diese klammer hier
  
  bool Ziehung::gezogen(int i)
  {

    bool neueZahl = true;
    for (int j=0;  j<i; j++)
    {
      if (lottozahl [j]==lottozahl[i])
      {
    neuezahl=false;
      }
    }
   return neueZahl;
  }