#include <iostream>
#include <thread>
struct S {    const int *p;  } s;  
const int **p = &s.p; 

//S *q = reinterpret_cast<S*>(p);
struct S1{ int*p;} ;

S1 *q1 = reinterpret_cast<S1*>(p);
int main()
{

}
