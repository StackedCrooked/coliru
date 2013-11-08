#include <iostream>

using namespace std;
 
#define MAX 5           // MAXIMUM CONTENTS IN QUEUE
 
class queue
{
 private:
    int t[MAX];
    int al;      // Addition End
    int dl;      // Deletion End

 

 public:
  queue();
  void del();
  void add(int item);
  void display();

};
