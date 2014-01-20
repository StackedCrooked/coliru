#include <iostream>
#include <iomanip>
#include <cstdarg>
#include <initializer_list>

enum                 {FLOAT, VEC2, VEC3};
int GLSL_SIZES[] = {    4,    8,   12};

float myfunc(std::initializer_list<float> l);

int main()
{
  std::cout << FLOAT << " " << GLSL_SIZES[FLOAT] << "\n";
  std::cout << VEC2  << " " << GLSL_SIZES[VEC2] << "\n";
  std::cout << VEC3  << " " << GLSL_SIZES[VEC3] << "\n";
  std::cout << "\n";
  
  myfunc(      { 1, 2 ,3, 4, 5, 6, 7, 8, 9,10,
                11,12,13,14,15,16,17,18,19,20,
                21,22,23,24,25,26,27,28,29,30,
                31,32,33,34,35,36,37,38,39,40,
                41,42,43,44,45,46,47,48,49,50,
                51,52,53,54,55,56,57,58,59,60,
                61,62,63,64,65,66,67,68,69,70,
                100.1234, myfunc({5,5,1}), -16777215 } ); 
}

float myfunc(std::initializer_list<float> l)
{
  float sum = 0;
  std::initializer_list<float>::iterator it;
  for ( it=l.begin(); it!=l.end(); ++it)
  {
    sum = sum + *it;
    std::cout << std::setprecision(8) << *it << "\n";
  }
  
  std::cout << "\n";
  return(sum);
}
