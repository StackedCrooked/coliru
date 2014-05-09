#include<omp.h>
#include<iostream>


struct point2d{
    int x;
    int y;
#ifndef DECLARE_AS_POD_TYPE    
    point2d() {
    }
#endif
    
};      

void fun() {
  using namespace std;
  extern point2d myPoint;
  #pragma omp threadprivate(myPoint)
  //point2d myPoint;
  myPoint.x = omp_get_thread_num();
  cout << myPoint.x << endl;
}

