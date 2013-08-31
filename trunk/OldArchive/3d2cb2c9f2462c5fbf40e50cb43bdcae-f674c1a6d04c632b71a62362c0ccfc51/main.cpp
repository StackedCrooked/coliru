#include <iostream>
#include <string>
#include <vector>

#include <time.h>       /* time_t, struct tm, time, localtime, strftime */
#include <locale.h> 
#include <stdio.h>
#include <assert.h>
#include <typeinfo>

using namespace std;

template <typename FROM, typename TO>
void Convert(FROM f)
{
  string fromName = typeid(FROM).name();
  string toName = typeid(TO).name();
  cout << "FROM: " << fromName << " TO: " << toName << endl << endl;
  
  cout << "FROM f  = " << f << endl;
    
  TO t1 {f}; // error: narrowing, e.g. from double to float -> COMPILER
  cout << "TO t1 {f};      t1 = " << t1 << endl;
    
  TO t2 = {f}; // error: narrowing, e.g. from double to float -> COMPILER WARNING
  cout << "TO t2 = {f};    t2 = " << t2 << endl;
  
  TO t3 = f; // error: narrowing, e.g. from double to float -> BUT NO COMPILER SUPPORT
  cout << "TO t3 = f;      t3 = " << t3 << endl;
  
  TO t4(f);
  cout << "TO t4(f);       t4 = " << t4 << endl;
    
  auto t5 = {f};
  cout << "auto t5 = {f};  t5 = " << typeid(t5).name() << endl;

  auto t6 {f};
  cout << "auto t6 {f};    t6 = " << typeid(t6).name() << endl;
  
  auto t7 = f;
  cout << "auto t7 = f;    t7 = " << t7 << endl;
  
  cout << endl;
}

int main()
{
  Convert<float, double>(0.5);
  Convert<double, float>(0.5);
  Convert<char, int>(75);
  Convert<int, char>(75);
  
  return 0;
}
