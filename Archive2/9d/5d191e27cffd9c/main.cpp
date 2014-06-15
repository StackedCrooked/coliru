#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <random>
#include <cmath>
float getMostFreq(float* LRArr,int sizeLRArr)
{
int count = 1;
int currentIndex = 0;
   for (int i = 1; i < sizeLRArr; i++)
   {
    if (LRArr[i] == LRArr[currentIndex])
        count++;
    else
        count--;
    if (count == 0)
    {
        currentIndex = i;
        count = 1;
    }
  }
 float mostFreq = LRArr[currentIndex];
  return mostFreq;
}
int main()
{
   int sizeLRArr=10;
   float *LRArr=new float[10];
   std::random_device rd;
   std::default_random_engine generator;
   generator.seed( rd() );
   std::uniform_real_distribution<> distribution(0, 6);
   for(int k=0;k<10;k++)
   {
       LRArr[k]=distribution(generator);
       std::cout<<LRArr[k]<<std::endl;
   }
   std::cout<<"Most Freq"<<getMostFreq(LRArr,10)<<std::endl;
   return 0;
}