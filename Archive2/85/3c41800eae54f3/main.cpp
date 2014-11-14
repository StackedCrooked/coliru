#include <iostream>
#include <stdio.h>
#include <chrono>
#include <cstdlib>
#include <ctime>
#define LOOPAMOUNT 100000000

int one();
int two();
int three();
int four();
int five();
int six();
int seven();
int eight();
int nine();
int ten();

int (*p[10]) (void);

int main(void)
{
  p[0] = one;
  p[1] = two;
  p[2] = three;
  p[3] = four;
  p[4] = five;
  p[5] = six;
  p[6] = seven;
  p[7] = eight;
  p[8] = nine;
  p[9] = ten;

  std::chrono::time_point<std::chrono::high_resolution_clock> start, start2, start3, end, end2, end3;

  unsigned long long v1 = 0;
  // Using function pointers
  start = std::chrono::high_resolution_clock::now();
  for(unsigned long long i = 0; i < LOOPAMOUNT; i++)
  {
    v1 += (*p[i % 10]) ();
  }
  end = std::chrono::high_resolution_clock::now();

  unsigned long long v2 = 0;

  // Using if statements
  start2 = std::chrono::high_resolution_clock::now();
  for(unsigned long long i = 0; i < LOOPAMOUNT; i++)
  {
     if(i % 10 == 0)      v2 += one();
     else if(i % 10 == 1) v2 += two();
     else if(i % 10 == 2) v2 += three();
     else if(i % 10 == 3) v2 += four();
     else if(i % 10 == 4) v2 += five();
     else if(i % 10 == 5) v2 += six();
     else if(i % 10 == 6) v2 += seven();
     else if(i % 10 == 7) v2 += eight();
     else if(i % 10 == 8) v2 += nine();
     else ten();
  }
  end2 = std::chrono::high_resolution_clock::now();

  unsigned long long v3 = 0;
  // Using switch
  start3 = std::chrono::high_resolution_clock::now();
  for(unsigned long long i = 0; i < LOOPAMOUNT; i++)
  {
    switch(i % 10)
    {
      case 0: one();   v3 += one();    break;
      case 1: two();   v3 += two();    break;
      case 2: three(); v3 += three();  break;
      case 3: four();  v3 += four();   break;
      case 4: five();  v3 += five();   break;
      case 5: six();   v3 += six();    break;
      case 6: seven(); v3 += seven();  break;
      case 7: eight(); v3 += eight();  break;
      case 8: nine();  v3 += nine();   break;
      case 9: ten();                   break;
    }
  }

  end3 = std::chrono::high_resolution_clock::now();

  std::chrono::duration<double> elapsed_seconds = end - start;
  std::chrono::duration<double> elapsed_seconds2 = end2 - start2;
  std::chrono::duration<double> elapsed_seconds3 = end3 - start3;

  std::cout << "Pointers: " << elapsed_seconds.count() <<"s\n" << "Number v1: " << v1 << "\n";
  std::cout << "Ifs: " << elapsed_seconds2.count() <<"s\n" << "Number v2: " << v2 << "\n";
  std::cout << "Switch: " << elapsed_seconds3.count() <<"s\n" << "Number v3: " << v3 << "\n";

  system("pause");
  return 0;
}

int one()
{
  return 1;
}

int two()
{
  return 2;
}

int three()
{
  return 3;
}

int four()
{
  return 4;
}

int five()
{
  return 5;
}

int six()
{
  return 6;
}

int seven()
{
  return 7;
}

int eight()
{
  return 8;
}

int nine()
{
  return 9;
}

int ten()
{
  return 10;
}