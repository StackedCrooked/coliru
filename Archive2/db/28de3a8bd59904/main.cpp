#include <sstream>
#include <vector>
#include <iostream>
#include <list>
#include <ctime>
using namespace std;

int randomNum(int min, int max){

   return rand() * (1.0 / (RAND_MAX + 1.0)) * (max - min);
}

unsigned time_seed(){ // implementation from online
   time_t now = time(NULL);
   unsigned char *p = (unsigned char *)&now;
   unsigned seed = 0;
   size_t i;

   for (i = 0; i < sizeof now; i++)
      seed = seed * (UCHAR_MAX + 2U) + p[i];

   return seed;
}

int main(){
    
   const int SIZE = 10000000, MAX_ELM = 10000000;
   list<int> sortedList;
   list<int> unsortedList;
   int indexToFind, itemToFind;

   srand(time_seed());
   indexToFind = SIZE/2;
   //initialize list
   for (int i = 0; i < SIZE; i++){      
      if (i == indexToFind){
         itemToFind = randomNum(0, MAX_ELM);
         sortedList.push_back(itemToFind);
      }
      else
         sortedList.push_back(randomNum(0, MAX_ELM));
   }

   unsortedList = sortedList; //copy ctr
   sortedList.sort();
   clock_t start, end;
   int sortedItemIndex = 0;

   //search for item in sorted list
   start = clock();
   list<int>::iterator it;
   for (it = sortedList.begin(); it != sortedList.end(); ++it){
      if ((*it) == itemToFind){
         break;
      }
      sortedItemIndex++;
   }
   end = clock();

   cout << "index: " << sortedItemIndex << "  item: " << itemToFind << endl; 
   cout << (double)(end - start) / (double)CLOCKS_PER_SEC << endl << endl;

   //unsorted
   start = clock();
   for (it = unsortedList.begin(); it != unsortedList.end(); ++it){
      if ((*it) == itemToFind)
         break;
   }
   end = clock();

   cout << "index: " << indexToFind << "  item: " << itemToFind << endl;
   cout << (double)(end - start) / (double)CLOCKS_PER_SEC << endl;

}