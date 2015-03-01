#include <fstream>
#include <iostream>
#include <complex>

using namespace std;

int main ()
{
  ofstream outFileInput,outFileOutput;
  complex<double> *pSignal = new complex<double>[1024];
  complex<double> *Output  = new complex<double>[1024];
  complex<double> valueC(1.0, 2.0);
  double value, pi = 3.1415926535897932384626;
  int N = 1024, nn = 0;
  outFileInput.open ("cppFFTinp.dat");
  outFileOutput.open("cppFFTout.dat");
}
