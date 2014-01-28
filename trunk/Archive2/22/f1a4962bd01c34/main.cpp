#include <iostream>
#include <cmath>

double A440 = 440;

int freqGetOctave(double f) {
  double a = 12*log2(f/(A440/16))+.505;
  int c = (int)(a+9)/12;
  return c;
}

int main()
{
    std::cout << freqGetOctave(440) << '\n';
}